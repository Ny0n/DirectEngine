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

void Component::NotifyInstantiation()
{
	if (this->_instantiatied) // safeguard
	{
		Utils::PrintErr("Component::NotifyInstantiation #1");
		return;
	}

	this->_instantiatied = true;
	this->_markedForInstantiation = true;
	Execution::markedForInstantiation.push_back(this);
	
	Awake();
	if (IsEnabled())
		OnEnable();
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

	if (gameObject != nullptr && gameObject->IsEnabled())
	{
		if (_enabledSelf)
			this->OnEnable();
		else
			this->OnDisable();
	}

	return true;
}

bool Component::IsEnabled()
{
	if (gameObject != nullptr)
		return gameObject->IsEnabled() && _enabledSelf;

	return _enabledSelf;
}
