#pragma once

class GameObject final : public Object
{

public:
	GameObject();
	
	template <typename T>
	T* GetComponent();								// Gets the first found component of the specified type on the GameObject

	template <typename T, typename... A>
	T* AddComponent(const A&... args);				// Creates and Adds a new component of the specified type to the GameObject (MAKE SURE that the specified component class has a constructor matching the arguments!)

	template <typename T>
	bool RemoveComponent();							// Destroys the first found component of the specified type on the GameObject

	bool AddComponent(Component* componentIn);		// Adds the given component to the GameObject
	bool RemoveComponent(Component* componentIn);	// Destroys the given component on the GameObject (if found)

	bool Destroy() final;
	bool SetEnabled(bool enabled) final;
	bool IsEnabled() final;

	string name;
	list<Component*> components;
	Transform* transform; // default component

private:
	friend class Execution;
	friend class Scene;

	~GameObject() override;

};

#include "GameObject.tpp"
