#pragma once

class Component;
class GameObject;

class Object
{
	friend class GameObject;
	friend class Component;

	Object() = default;

public:
	bool IsDestructionPending();

	virtual bool SetEnabled(bool enabled);
	virtual bool IsEnabled();
	bool IsEnabledSelf();

	static bool Instantiate(GameObject* go); // instantiation method for GO, see GameObject::AddComponent for component instantiation
	static bool Destroy(GameObject* go);

	bool IsAlive();
	
private:
	friend class Execution;
	friend class Scene;

	static void TryToDelete(Object* obj);

	virtual bool PrivateDestroy();
	virtual void ApplyDestruction() = 0;
	virtual ~Object() = default;
	virtual bool NotifyInstantiation();

	bool _enabledSelf = true;

	// FLAGS
	bool _instantiatied = false;
	bool _destroyed = false;
	bool _markedForDestruction = false;

};
