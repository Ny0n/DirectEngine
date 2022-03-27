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

	static bool Instantiate(GameObject* go);
	static bool Destroy(Object* obj);

	bool IsAlive();

private:
	friend class Execution;

	virtual bool PrivateDestroy();
	virtual ~Object() = default;

	bool _enabledSelf = true;

	bool _markedForInstantiation = false; // has it been marked for scene instantiation?
	bool _instantiated = false; // has it been instantiated in the scene?
	bool _markedForDestruction = false;

};
