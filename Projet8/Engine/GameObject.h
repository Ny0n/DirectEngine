#pragma once

class Transform;

class GameObject final
{

public:
	GameObject();
	~GameObject();

	Component* GetComponent(const char* type);
	bool AddComponent(Component* component);
	bool RemoveComponent(const char* type);
	bool RemoveComponent(Component* component);
	
	void Destroy();

	list<Component*> components;
	Transform* transform; // default component
	
};
