#pragma once

#include "EngineLib.h"

class GoUpAndRoll : public Component
{

public:
	const char* GetType() override { return NAMEOF(GoUpAndRoll); }
	ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	void Update(float runTime, float deltaTime) override;

};
