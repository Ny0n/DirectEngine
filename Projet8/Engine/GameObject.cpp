#include "pch.h"

GameObject::GameObject() : transform(new Transform())
{
}

GameObject::~GameObject()
{
	delete transform;
	for (Component* component : components)
		component->OnDestroy();
	
	SceneManager::Remove(this);

	Utils::DeleteList(components);
}

// **************************** //

// Finds and returns the first fount component of type ComponentType
// Returns nullptr if not found
Component* GameObject::GetComponent(const char* type)
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
	if (component->CategoryEquals(ComponentCategory::single))
	{
		for (Component* element : components)
		{
			if (element->TypeEquals(component)) // no duplicate components
				return false;
		}
	}

	component->gameObject = this;
	component->transform = transform;
	components.push_back(component);
	return true;
}

// Removes and deletes the first component of type ComponentType found on the gameobject
bool GameObject::RemoveComponent(const char* type)
{
	if (Utils::Contains(&unremovableEngineComponents, type)) // unremovable components
		return false;

	for (Component* component : components)
	{
		if (component->TypeEquals(type))
		{
			components.remove(component);
			delete(component);
			return true;
		}
	}
	return false;
}

bool GameObject::RemoveComponent(Component* component)
{
	return RemoveComponent(component->GetType());
}

void GameObject::Destroy()
{
	delete(this);
}
