#include "pch.h"

GameObject::GameObject() : name("Default Name")
{
	const auto defaultTransform = new Transform();
	AddComponent(defaultTransform);
	transform = defaultTransform; // easy access
}

GameObject::~GameObject() // TODO redo when children
{
	list<Component*> componentsCopy(_components); // safeguard
	_components.clear();
	
	for (auto component : componentsCopy)
		Object::TryToDelete(component);
	
	componentsCopy.clear();
	
	SceneManager::Remove(this); // TODO remove from parent if parent, scene if no parent
}

void GameObject::ApplyDestruction()
{
	_destroyed = true;
	delete(this);
}

bool GameObject::NotifyInstantiation()
{
	if (!Object::NotifyInstantiation())
	{
		Utils::PrintErr("GameObject::NotifyInstantiation #1");
		return false;
	}

	this->_instantiatied = true;

	ForEachSelfComponent([](Component* component)
	{
		component->NotifyInstantiation();
	}, false);

	ForEachChildrenGameObject([](GameObject* go)
	{
		go->NotifyInstantiation();
	});

	return true;
}

// **************************** //

bool GameObject::AddComponent(Component* componentIn)
{
	if (componentIn == nullptr || this->IsDestructionPending())
	{
		Utils::PrintErr("GameObject::AddComponent #1");
		return false;
	}

	if (Utils::Contains(&_components, componentIn))
	{
		Utils::PrintErr("GameObject::AddComponent #2");
		return false;
	}

	if (componentIn->_instantiatied || componentIn->IsDestructionPending())
	{
		Utils::PrintErr("GameObject::AddComponent #3");
		return false;
	}

	if (componentIn->gameObject != nullptr)
	{
		Utils::PrintErr("GameObject::AddComponent #4");
		return false;
	}

	if (componentIn->CategoryEquals(ComponentCategory::single))
	{
		for (Component* component : _components)
		{
			if (component->IsDestructionPending()) // we consider that a to-be-destroyed component doesn't count (we also can't GetComponent a to-be-destroyed one either)
				continue;

			if (component->TypeEquals(componentIn))
			{
				Utils::PrintErr("GameObject::AddComponent #5"); // no duplicate 'single' category components
				return false;
			}
		}
	}

	componentIn->gameObject = this;
	componentIn->transform = transform;
	
	_components.push_back(componentIn);
	if (!Application::IsGeneratingScene() && _instantiatied) // at runtime, when we need to call Awake (and maybe Start) instantly (pas ultra sûr de cette condition)
		componentIn->NotifyInstantiation();

	return true;
}

bool GameObject::RemoveComponent(Component* componentIn)
{
	if (componentIn == nullptr || this->IsDestructionPending())
	{
		Utils::PrintErr("GameObject::RemoveComponent #1");
		return false;
	}

	if (!Utils::Contains(&_components, componentIn))
	{
		Utils::PrintErr("GameObject::RemoveComponent #2");
		return false;
	}

	if (Application::IsGeneratingScene() || componentIn->IsDestructionPending())
	{
		Utils::PrintErr("GameObject::RemoveComponent #3");
		return false;
	}

	if (Utils::Contains(&EngineComponent::unremovableEngineComponents, componentIn->GetType())) // unremovable components
	{
		Utils::PrintErr("GameObject::RemoveComponent #4");
		return false;
	}
	
	componentIn->PrivateDestroy();
	return true;
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
		if (!component->_markedForDestruction && component->_instantiatied) // safeguard
		{
			if (component->IsEnabledSelf())
			{
				if (IsEnabled()) // enabling
					component->NotifyEnabled(); // we fire the OnEnable only if the component is enabled too
				else // disabling
					component->NotifyDisabled(); // we fire the OnDisable only if the component wasn't already disabled
			}
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
