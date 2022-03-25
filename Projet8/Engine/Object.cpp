#include "pch.h"

bool Object::Destroy()
{
	if (!Application::IsPlaying())
		return false;
	
	if (_markedForDestruction)
		return false;

	return true;
}

bool Object::IsDestructionPending()
{
	return _markedForDestruction;
}

// **************************** //

bool Object::SetEnabled(bool enabled)
{
	if (_markedForDestruction) // we can only change its enabled state if it's not marked for destruction
		return false;

	if (_enabledSelf == enabled)
		return false;

	_enabledSelf = enabled;

	if (!Application::IsPlaying())
		return false;

	return true;
}

bool Object::IsEnabled() // overide in sub classes if necessary
{
	return _enabledSelf;
}

bool Object::IsEnabledSelf()
{
	return _enabledSelf;
}

bool Object::IsAlive() // temp
{
	return !IsDestructionPending() && IsEnabled();
}

// **************************** //

bool Object::Instantiate(GameObject* go)
{
	if (!Utils::Contains(&Execution::goMarkedForInstantiation, go))
	{
		Execution::goMarkedForInstantiation.push_back(go);

		list<Component*> copy(go->components); // safeguard
		if (go->IsEnabled())
		{
			for (auto component : copy)
			{
				if (!component->IsEnabled())
					continue;

				component->Awake(); // TODO awake
				component->OnEnable();
			}
		}
		copy.clear();

		return true;
	}
	return false;
}
