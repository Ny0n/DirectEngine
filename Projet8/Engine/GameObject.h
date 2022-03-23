#pragma once

class GameObject final
{

public:
	GameObject();
	~GameObject();
	
	template <typename T> T* GetComponent();		// Gets the first found component of the specified type on the GameObject
	bool AddComponent(Component* component);		// Adds the given component to the GameObject
	template <typename T> T* AddComponent();		// Creates and Adds a new component of the specified type to the GameObject
	template <typename T> bool RemoveComponent();	// Destroys the first found component of the specified type on the GameObject
	bool RemoveComponent(Component* component);		// Destroys the given component on the GameObject (if found)
	
	void Destroy() const;

	list<Component*> components;
	Transform* transform; // default component
	
};

#include "GameObject.tpp"
