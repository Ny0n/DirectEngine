#include "pch.h"

list<const char*> engineDefaultComponentTypes = { // components that we can't remove
	NAMEOF(Transform),
};

list<const char*> engineComponentTypes = { // engine-created components
	NAMEOF(Transform),
	NAMEOF(Camera),
	NAMEOF(MeshRenderer),
};

bool Component::TypeEquals(Component* other)
{
	return this->GetType() == other->GetType();
}

bool Component::TypeEquals(const char* other)
{
	return strcmp(this->GetType(), other) == 0  ;
}

bool Component::CategoryEquals(Component* other)
{
	return this->GetCategory() == other->GetCategory();
}

bool Component::CategoryEquals(const ComponentCategory other)
{
	return this->GetCategory() == other;
}
