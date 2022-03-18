#pragma once

#include "EngineLib.h"

class Move : public Component
{

public:
	const char* GetType() override { return NAMEOF(Move); }
	ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	Move() = default;
	explicit Move(float speed);

	void Update(float runTime, float deltaTime) override;

private:
	float _speed{ 10.0f };

};
