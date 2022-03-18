#pragma once

class Transform;

class GameObject
{

public:
	GameObject();
	virtual ~GameObject();

	Component* GetComponent(const char* type);
	bool AddComponent(Component* component);
	bool RemoveComponent(const char* type);
	bool RemoveComponent(Component* component);

	list<Component*> components;
	Transform* transform; // default component
	
};
