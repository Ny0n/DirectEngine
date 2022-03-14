#include "pch.h"

#include "Component.h"

bool Component::TypeEquals(Component* other)
{
	return this->GetType() == other->GetType();
}

bool Component::TypeEquals(ComponentType otherType)
{
	return this->GetType() == otherType;
}
