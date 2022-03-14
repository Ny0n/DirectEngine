#pragma once

enum class ComponentType
{
	transform,
	mesh,
	movable_cube
};

class Component
{

public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Start();
	virtual void Update(float runTime, float deltaTime);

	ComponentType type;
	bool typeEquals(Component* other);
	bool typeEquals(ComponentType other);

};
