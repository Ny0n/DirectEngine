#include "pch.h"

#include "Component.h"

#include "Utils.h"

void Component::Start()
{
}

void Component::Update(float runTime, float deltaTime)
{
}

bool Component::typeEquals(Component* other)
{
	return this->type == other->type;
}

bool Component::typeEquals(ComponentType other)
{
	return this->type == type;
}
