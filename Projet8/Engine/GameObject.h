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

	list<Component*> GetComponents();				// Gets the component list for the go
	bool AddComponent(Component* componentIn);		// Adds the given component to the GameObject
	bool RemoveComponent(Component* componentIn);	// Destroys the given component on the GameObject (if found)

	bool SetEnabled(bool enabled) final;
	bool IsEnabled() final;

	string name;
	Transform* transform; // default component

	void ForEachGameObject(const function<void(GameObject*)>& consumer, bool onlyAlive = true);
	void ForEachComponent(const function<void(Component*)>& consumer, bool onlyAlive = true);

	void ForEachChildrenGameObject(const function<void(GameObject*)>& consumer, bool onlyAlive = true);
	void ForEachSelfComponent(const function<void(Component*)>& consumer, bool onlyAlive = true);

private:
	friend class Execution;
	friend class SceneManager;
	friend class Scene;
	friend class Object;
	friend class Component;

	bool PrivateDestroy() final;
	void ApplyDestruction() final;
	~GameObject() override;

	void NotifyInstantiation();

	list<Component*> _components;
	// list<GameObject*> _children;

};

#include "GameObject.tpp"
