#include "pch.h"

Component::~Component()
{
	if (gameObject != nullptr)
		gameObject->components.remove(this);
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

bool Component::Destroy()
{
	if (!Object::Destroy())
		return false;
	
	Execution::compMarkedForDestruction.push_back(this);
	_markedForDestruction = true;

	return true;
}

bool Component::SetEnabled(bool enabled)
{
	if (!Object::SetEnabled(enabled))
		return false;
	
	if (IsEnabled())
		this->OnEnable();
	else
		this->OnDisable();

	return true;
}

bool Component::IsEnabled()
{
	if (gameObject != nullptr)
		return gameObject->IsEnabled() && _enabledSelf;

	return _enabledSelf;
}
