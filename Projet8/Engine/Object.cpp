#include "pch.h"

bool Object::PrivateDestroy() // helper for sub-classes (overriden)
{
	if (!Application::IsPlaying() || Application::IsGeneratingScene()) // TODO recheck si ces trucs sont utiles mnt
	{
		Utils::PrintErr("Object::PrivateDestroy #1");
		return false;
	}
	
	if (_markedForDestruction || !_markedForInstantiation)
	{
		Utils::PrintErr("Object::PrivateDestroy #2");
		return false;
	}

	return true;
}

bool Object::IsDestructionPending()
{
	return _markedForDestruction;
}

// **************************** //

bool Object::SetEnabled(bool enabled) // helper for sub-classes (overriden)
{
	if (_markedForDestruction)
	{
		Utils::PrintErr("Object::SetEnabled #1"); // we can only change its enabled state if it's not marked for destruction
		return false;
	}

	if (_enabledSelf == enabled)
	{
		Utils::PrintErr("Object::SetEnabled #2");
		return false;
	}

	_enabledSelf = enabled;

	if (!Application::IsPlaying() || Application::IsGeneratingScene())
	{
		Utils::PrintErr("Object::SetEnabled #3");
		return false;
	}

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

bool Object::Instantiate(GameObject* go) // instantiation method for GO, see AddComponent for component instantiation TODO instantiate as child / other pos?
{
	if (!Application::IsPlaying() || Application::IsGeneratingScene() || go == nullptr)
	{
		Utils::PrintErr("Object::Instantiate #1");
		return false;
	}

	if (go->_markedForInstantiation)
	{
		Utils::PrintErr("Object::Instantiate #2"); // we can't instantiate an object that's already here
		return false;
	}

	if (!Utils::Contains(&Execution::goMarkedForInstantiation, go))
	{
		Execution::goMarkedForInstantiation.push_back(go);
		go->NotifyInstantiation();

		return true;
	}

	Utils::PrintErr("Object::Instantiate #3"); // should never happen
	return false;
}

bool Object::Destroy(Object* obj)
{
	if (!Application::IsPlaying() || Application::IsGeneratingScene() || obj == nullptr)
	{
		Utils::PrintErr("Object::Destroy #1");
		return false;
	}
	
	return obj->PrivateDestroy();
}
