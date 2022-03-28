#pragma once

class GameObject;
class Transform;

enum class ComponentCategory
{
	single,
	multiple,
};

class Component : public Object
{
	friend class EngineComponent;
	friend class MonoBehaviour;

	Component() = default;

public:
	virtual string GetType() = 0;
	virtual ComponentCategory GetCategory() = 0;

	bool TypeEquals(Component* other);
	bool TypeEquals(const string& other);
	bool CategoryEquals(Component* other);
	bool CategoryEquals(const ComponentCategory other);

	virtual void Awake() {}
	virtual void OnEnable() {}
	virtual void Start() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void OnDisable() {}
	virtual void OnDestroy() {}

	virtual void EngineStart() = 0;
	virtual void EngineUpdate() = 0;

	virtual void OnCollideEnter(GameObject* other) {}
	virtual void OnCollide(GameObject* other) {}
	virtual void OnCollideExit(GameObject* other) {}

	bool SetEnabled(bool enabled) final;
	bool IsEnabled() final;

	GameObject* gameObject;
	Transform* transform;

private:
	friend class Execution;
	friend class SceneManager;
	friend class Object;
	friend class GameObject;

	bool PrivateDestroy() final;
	void ApplyDestruction() final;
	~Component() override;

	void NotifyInstantiation();

	void NotifyEnabled();
	void NotifyDisabled();

	void CheckIfEngineStarted();
	void CheckIfStarted();
	bool _engineStarted = false;
	bool _started = false;

};
