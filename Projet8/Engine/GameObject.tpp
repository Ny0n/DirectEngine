#pragma once

template <typename T>
T* GameObject::GetComponent()
{
	const string type = NAMEOF(T);

	for (Component* component : components)
	{
		if (component->TypeEquals(type))
			return static_cast<T*>(component);
	}

	return nullptr;
}

template <typename T>
T* GameObject::AddComponent()
{
	Component* component = new T();

	if (AddComponent(component))
		return component;

	return nullptr;
}

template <typename T>
bool GameObject::RemoveComponent()
{
	const string type = NAMEOF(T);

	if (Utils::Contains(&EngineComponent::unremovableEngineComponents, type)) // unremovable components
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
