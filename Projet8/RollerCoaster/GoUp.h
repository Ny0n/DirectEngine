#pragma once

#include "EngineLib.h"

class GoUp : public Component
{

public:
	const char* GetType() override { return NAMEOF(GoUp); }
	ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	GoUp() = default;
	explicit GoUp(float speed);

	void Update() override;

private:
	float _speed{ 1.0f };

};
