#pragma once

class Component;
class GameObject;

class Object
{
	friend class GameObject;
	friend class Component;

	Object() = default;

public:
	virtual bool Destroy();
	bool IsDestructionPending();

	virtual bool SetEnabled(bool enabled);
	virtual bool IsEnabled();
	bool IsEnabledSelf();

	bool Instantiate(GameObject* go);

	bool IsAlive();

private:
	friend class Execution;

	virtual ~Object() = default;

	bool _enabledSelf = true;
	bool _markedForDestruction = false;

};
