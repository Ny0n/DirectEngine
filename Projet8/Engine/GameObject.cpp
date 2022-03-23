#include "pch.h"

GameObject::GameObject()
{
	const auto defaultTransform = new Transform();
	AddComponent(defaultTransform);
	transform = defaultTransform; // easy access
}

GameObject::~GameObject()
{
	for (Component* component : components)
		component->OnDestroy();
	
	SceneManager::Remove(this);

	Utils::DeleteList(components);
}

// **************************** //

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

bool GameObject::RemoveComponent(Component* componentIn)
{
	if (Utils::Contains(&EngineComponent::unremovableEngineComponents, componentIn->GetType())) // unremovable components
		return false;

	for (Component* component : components)
	{
		if (component == componentIn)
		{
			components.remove(component);
			delete(component);
			return true;
		}
	}
	return false;
}

void GameObject::Destroy() const
{
	delete(this);
}
