#pragma once

extern list<const char*> engineDefaultComponentTypes;
extern list<const char*> engineComponentTypes;

enum class ComponentCategory
{
	unique,
	behaviour,
};

class Component
{

public:
	virtual const char* GetType() = 0; // a pure function makes the class abstract
	virtual ComponentCategory GetCategory() = 0;

	virtual ~Component() = default;

	virtual void Start(){}
	virtual void Update(){}
	virtual void LateUpdate(){}
	virtual void FixedUpdate(){}

	bool TypeEquals(Component* other);
	bool TypeEquals(const char* other);
	bool CategoryEquals(Component* other);
	bool CategoryEquals(const ComponentCategory other);

public:
	GameObject* gameObject;
	Transform* transform;

};
