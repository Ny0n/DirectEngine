#include "pch.h"

#include "GameObject.h"

GameObject::GameObject() : transform(new Transform())
{
}

GameObject::~GameObject()
{
	for (const Component* component : this->components)
	{
		delete(component);
	}

	delete transform;
	components.clear();
}

// Finds and returns the first fount component of type ComponentType
// Returns nullptr if not found
Component* GameObject::GetComponent(ComponentType type) const
// TODO for get and remove, change type for mono_behaviour (tout changer pour typeid() ?)
{
	for (Component* component : components)
	{
		if (component->TypeEquals(type))
			return component;
	}
	return nullptr;
}

// Adds the given component to the gameobject
// A gameobject can only have one of each time of component, EXCEPT for mono_behaviour types
bool GameObject::AddComponent(Component* component)
{
	if (!component->TypeEquals(ComponentType::mono_behaviour)) // there can have multiple mono_behaviour on a gameobject
	{
		for (Component* element : components)
		{
			if (element->TypeEquals(component)) // no duplicate components
				return false;
		}
	}

	components.push_back(component);
	return true;
}

// Removes the first component of type ComponentType found on the gameobject
bool GameObject::RemoveComponent(ComponentType type)
{
	if (type == ComponentType::transform) // we can't remove the transform
		return false;

	for (Component* element : components)
	{
		if (element->TypeEquals(type))
		{
			components.remove(element);
			delete(element);
			return true;
		}
	}
	return false;
}

bool GameObject::RemoveComponent(Component* component)
{
	return RemoveComponent(component->GetType());
}
