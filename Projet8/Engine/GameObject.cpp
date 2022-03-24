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

bool GameObject::AddComponent(Component* componentIn)
{
	if (componentIn == nullptr)
		return false;

	if (componentIn->CategoryEquals(ComponentCategory::single))
	{
		for (Component* component : components)
		{
			if (component->TypeEquals(componentIn)) // no duplicate components
				return false;
		}
	}

	componentIn->gameObject = this;
	componentIn->transform = transform;
	components.push_back(componentIn);
	return true;
}

bool GameObject::RemoveComponent(Component* componentIn)
{
	if (componentIn == nullptr)
		return false;

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
