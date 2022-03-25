#include "pch.h"

GameObject::GameObject() : name("Default Name")
{
	const auto defaultTransform = new Transform();
	AddComponent(defaultTransform);
	transform = defaultTransform; // easy access
}

GameObject::~GameObject()
{
	list<Component*> componentsCopy(components); // safeguard

	for (auto element : componentsCopy)
	{
		element->OnDestroy();
		delete(element);
	}

	componentsCopy.clear();

	components.clear();

	SceneManager::Remove(this);
}

// **************************** //

bool GameObject::AddComponent(Component* componentIn)
{
	if (componentIn->IsDestructionPending())
		return false;

	if (componentIn == nullptr)
		return false;

	if (componentIn->CategoryEquals(ComponentCategory::single))
	{
		for (Component* component : components)
		{
			if (component->IsDestructionPending())
				continue;

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
	if (componentIn->IsDestructionPending())
		return false;

	if (componentIn == nullptr)
		return false;

	if (Utils::Contains(&EngineComponent::unremovableEngineComponents, componentIn->GetType())) // unremovable components
		return false;

	for (Component* component : components)
	{
		if (component->IsDestructionPending())
			continue;

		if (component == componentIn)
		{
			component->Destroy();
			return true;
		}
	}
	return false;
}

// **************************** //

bool GameObject::Destroy()
{
	if (!Object::Destroy())
		return false;

	Execution::goMarkedForDestruction.push_back(this);
	_markedForDestruction = true;

	return true;
}

bool GameObject::SetEnabled(bool enabled)
{
	if (!Object::SetEnabled(enabled))
		return false;
	
	list<Component*> copy(this->components); // safeguard
	if (IsEnabled()) // enabling
	{
		for (auto element : copy)
			element->OnEnable();
	}
	else // disabling
	{
		for (auto element : copy)
		{
			if (element->IsEnabledSelf()) // we fire the OnDisable only if the component wasn't already disabled
				element->OnDisable();
		}
	}
	copy.clear();

	return true;
}

bool GameObject::IsEnabled()
{
	return Object::IsEnabled(); // TODO LATER change if we ever have a parent game object
}
