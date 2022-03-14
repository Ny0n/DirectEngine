#pragma once

enum class ComponentType
{
	mono_behaviour,
	transform,
	camera,
};

class Component
{

public:
	virtual ComponentType GetType() = 0; // this makes the class abstract

	virtual ~Component() = default;

	virtual void Start(){}
	virtual void Update(float runTime, float deltaTime){}

	bool TypeEquals(Component* other);
	bool TypeEquals(ComponentType other);

};
