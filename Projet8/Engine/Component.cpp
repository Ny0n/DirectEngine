#include "pch.h"

Component::~Component()
{
	if (gameObject != nullptr)
		gameObject->_components.remove(this);
}

void Component::ApplyDestruction()
{
	if (!_markedForDestruction)
		OnDestroy();
	delete(this);
}

bool Component::NotifyInstantiation()
{
	if (!Object::NotifyInstantiation())
	{
		Utils::PrintErr("Component::NotifyInstantiation #1");
		return false;
	}

	this->_instantiatied = true;
	
	Awake();
	if (!Time::inSceneStep) // later at runtime, not when we load a scene
	{
		this->CheckIfEngineStarted();
		this->CheckIfStarted();
	}

	return true;
}

// **************************** //

bool Component::TypeEquals(Component* other)
{
	return this->GetType() == other->GetType();
}

bool Component::TypeEquals(const string& other)
{
	return this->GetType() == other;
}

bool Component::CategoryEquals(Component* other)
{
	return this->GetCategory() == other->GetCategory();
}

bool Component::CategoryEquals(const ComponentCategory other)
{
	return this->GetCategory() == other;
}

// **************************** //

bool Component::PrivateDestroy()
{
	if (!Object::PrivateDestroy())
	{
		Utils::PrintErr("Component::PrivateDestroy #1");
		return false;
	}
	
	_markedForDestruction = true;
	Execution::markedForDestruction.push_back(this);

	OnDestroy();

	return true;
}

bool Component::SetEnabled(bool enabled)
{
	if (!Object::SetEnabled(enabled))
	{
		Utils::PrintErr("Component::SetEnabled #1");
		return false;
	}

	if (gameObject == nullptr) // just in case, but there SHOULD be a gameObject if we're here, because we can only get here if we're instantiated
	{
		Utils::PrintErr("Component::SetEnabled #2");
		return false;
	}

	if (gameObject->IsEnabled())
	{
		if (_enabledSelf)
			this->NotifyEnabled();
		else
			this->NotifyDisabled();
	}

	return true;
}

bool Component::IsEnabled()
{
	if (gameObject != nullptr)
		return gameObject->IsEnabled() && _enabledSelf;

	return _enabledSelf;
}

void Component::NotifyEnabled()
{
	this->CheckIfEngineStarted();
	this->CheckIfStarted();
	this->OnEnable();
}

void Component::NotifyDisabled()
{
	this->OnDisable();
}

void Component::CheckIfEngineStarted()
{
	if (!_engineStarted)
	{
		this->EngineStart();
		_engineStarted = true;
	}
}

void Component::CheckIfStarted()
{
	if (!_started)
	{
		this->Start();
		_started = true;
	}
}