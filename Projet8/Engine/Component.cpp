#include "pch.h"

Component::~Component()
{
	Execution::startedEngineComponents.remove(this);
	Execution::startedComponents.remove(this);

	if (gameObject != nullptr)
		gameObject->components.remove(this);
}

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

void Component::Destroy() const
{
	delete(this);
}
