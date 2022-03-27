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
	if (this->_markedForInstantiation) // safeguard
	{
		Utils::PrintErr("Component::NotifyInstantiation #1");
		return;
	}

	this->_markedForInstantiation = true;
	
	Awake();
	if (IsEnabled())
		OnEnable();
}

void Component::ApplyInstantiation()
{
	gameObject->_components.push_back(this); // TODO do 2 lists.........
	_instantiated = true;
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
	
	Execution::compMarkedForDestruction.push_back(this);
	_markedForDestruction = true;

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
