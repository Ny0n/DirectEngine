#pragma once

class GameObject;
class Transform;

enum class ComponentCategory
{
	single,
	multiple,
};

class Component
{
	friend class EngineComponent;
	friend class MonoBehaviour;

	Component() = default;

public:
	virtual ~Component();
	virtual string GetType() = 0;
	virtual ComponentCategory GetCategory() = 0;

	bool TypeEquals(Component* other);
	bool TypeEquals(const string& other);
	bool CategoryEquals(Component* other);
	bool CategoryEquals(const ComponentCategory other);

	void Destroy() const;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void FixedUpdate() = 0;

	virtual void EngineStart() = 0;
	virtual void EngineUpdate() = 0;

	virtual void Awake() {}
	virtual void OnDestroy(){}
	virtual void OnEnable(){}
	virtual void OnDisable(){}
	virtual void OnCollide(GameObject* other) {}

	GameObject* gameObject;
	Transform* transform;

};
