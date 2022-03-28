#include "pch.h"

bool Object::PrivateDestroy() // helper for sub-classes (overriden)
{
	if (!Application::IsPlaying() || Application::IsGeneratingScene()) // TODO recheck si ces trucs sont utiles mnt
	{
		Utils::PrintErr("Object::PrivateDestroy #1");
		return false;
	}
	
	if (_markedForDestruction || !_instantiatied)
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

	if (!Application::IsPlaying() || !_instantiatied)
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

bool Object::IsAlive()
{
	return !_markedForDestruction && _instantiatied && IsEnabled();
}

void Object::TryToDelete(Object* obj) // I'M NOT VERY PROUD OF THIS, but since i don't have the time to pententially pass everything to unique_ptr, this will do
{
	try
	{
		obj->ApplyDestruction();
	}
	catch (...)
	{
	}
}

// **************************** //

bool Object::Instantiate(GameObject* go) // TODO instantiate as child / other pos?
{
	if (!Application::IsPlaying() || Application::IsGeneratingScene() || go == nullptr)
	{
		Utils::PrintErr("Object::Instantiate #1");
		return false;
	}

	if (go->_instantiatied)
	{
		Utils::PrintErr("Object::Instantiate #2"); // we can't instantiate an object that's already here
		return false;
	}

	// TODO soit il s'ajoute au parent si il en a un, soit il s'ajoute a la scene
	SceneManager::Instantiate(go);
	go->NotifyInstantiation();

	return true;
}

bool Object::Destroy(GameObject* go)
{
	if (!Application::IsPlaying() || Application::IsGeneratingScene() || go == nullptr)
	{
		Utils::PrintErr("Object::Destroy #1");
		return false;
	}
	
	return go->PrivateDestroy();
}
