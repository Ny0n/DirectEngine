#pragma once

#include "Transform.h"

class GameObject
{

public:
	GameObject();
	virtual ~GameObject();

	Component* GetComponent(ComponentType type) const;
	bool AddComponent(Component* component);
	bool RemoveComponent(ComponentType type);
	bool RemoveComponent(Component* component);

	list<Component*> components;
	Transform* transform; // default component
	
};
