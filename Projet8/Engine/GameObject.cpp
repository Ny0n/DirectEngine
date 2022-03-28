﻿#include "pch.h"

GameObject::GameObject() : name("Default Name")
{
	const auto defaultTransform = new Transform();
	AddComponent(defaultTransform);
	transform = defaultTransform; // easy access
}

GameObject::~GameObject() // TODO redo when children
{
	list<Component*> componentsCopy(_components); // safeguard
	
	for (auto component : componentsCopy)
		Object::TryToDelete(component);
	
	componentsCopy.clear();
	
	_components.clear();
	
	SceneManager::Remove(this); // TODO remove from parent if parent, scene if no parent
}

void GameObject::ApplyDestruction()
{
	delete(this);
}

void GameObject::NotifyInstantiation()
{
	if (this->_instantiatied) // safeguard
	{
		Utils::PrintErr("GameObject::NotifyInstantiation #1");
		return;
	}

	this->_instantiatied = true;

	ForEachSelfComponent([](Component* component)
	{
		component->NotifyInstantiation();
	}, false); // TODO recheck onlyAlive de partout

	ForEachChildrenGameObject([](GameObject* go)
	{
		go->NotifyInstantiation();
	});
}

// **************************** //

bool GameObject::AddComponent(Component* componentIn) // TODO PROTECT THIS (only use templated versions?) // TODO verify if component is not already in the _components (same for GO)
{
	if (componentIn == nullptr)
	{
		Utils::PrintErr("GameObject::AddComponent #1");
		return false;
	}

	if (componentIn->_instantiatied)
	{
		Utils::PrintErr("GameObject::AddComponent #2");
		return false;
	}

	if (componentIn->CategoryEquals(ComponentCategory::single))
	{
		for (Component* component : _components)
		{
			if (component->IsDestructionPending()) // we consider that a to-be-destroyed component doesn't count
				continue;

			if (component->TypeEquals(componentIn)) // no duplicate components
			{
				Utils::PrintErr("GameObject::AddComponent #3");
				return false;
			}
		}
	}

	componentIn->gameObject = this;
	componentIn->transform = transform;
	
	_components.push_back(componentIn);
	if (!Application::IsGeneratingScene() && _instantiatied) // TODO recheck this
		componentIn->NotifyInstantiation();

	return true;
}

bool GameObject::RemoveComponent(Component* componentIn)
{
	if (componentIn == nullptr)
	{
		Utils::PrintErr("GameObject::RemoveComponent #1");
		return false;
	}

	if (componentIn->IsDestructionPending())
	{
		Utils::PrintErr("GameObject::RemoveComponent #2");
		return false;
	}

	if (Utils::Contains(&EngineComponent::unremovableEngineComponents, componentIn->GetType())) // unremovable components
	{
		Utils::PrintErr("GameObject::RemoveComponent #3");
		return false;
	}

	for (Component* component : _components)
	{
		if (component->IsDestructionPending())
			continue;

		if (component == componentIn)
		{
			component->PrivateDestroy();
			return true;
		}
	}

	Utils::PrintErr("GameObject::PrivateDestroy #4"); // component not found
	return false;
}

list<Component*> GameObject::GetComponents()
{
	return { _components };
}

// **************************** //

bool GameObject::PrivateDestroy()
{
	if (!Object::PrivateDestroy())
	{
		Utils::PrintErr("GameObject::PrivateDestroy #1");
		return false;
	}

	_markedForDestruction = true;
	Execution::markedForDestruction.push_back(this);
	
	ForEachSelfComponent([](Component* component)
	{
		component->PrivateDestroy();
	});

	ForEachChildrenGameObject([](GameObject* go)
	{
		go->PrivateDestroy();
	});

	return true;
}

bool GameObject::SetEnabled(bool enabled)
{
	if (!Object::SetEnabled(enabled))
	{
		Utils::PrintErr("GameObject::SetEnabled #1");
		return false;
	}
	
	ForEachComponent([&](Component* component)
	{
		if (component->IsEnabledSelf())
		{
			if (IsEnabled()) // enabling
				component->NotifyEnabled(); // we fire the OnEnable only if the component is enabled too
			else // disabling
				component->NotifyDisabled(); // we fire the OnDisable only if the component wasn't already disabled
		}
	}, false);

	return true;
}

bool GameObject::IsEnabled()
{
	return Object::IsEnabled(); // TODO LATER change if we ever have a parent game object
}

// **************************** //

void GameObject::ForEachGameObject(const function<void(GameObject*)>& consumer, bool onlyAlive)
{
	if (!onlyAlive || this->IsAlive())
		consumer(this);

	ForEachChildrenGameObject(consumer, onlyAlive);
}

void GameObject::ForEachComponent(const function<void(Component*)>& consumer, bool onlyAlive)
{
	ForEachGameObject([&](GameObject* go)
	{
		go->ForEachSelfComponent(consumer, onlyAlive);
	}, onlyAlive);
}

void GameObject::ForEachChildrenGameObject(const function<void(GameObject*)>& consumer, bool onlyAlive)
{
	// for (auto go : _children)
	// {
	// 	if (!onlyAlive || go->IsAlive())
	// 		consumer(go);
	// }
}

void GameObject::ForEachSelfComponent(const function<void(Component*)>& consumer, bool onlyAlive)
{
	for (Component* component : _components)
	{
		if (!onlyAlive || component->IsAlive())
			consumer(component);
	}
}
