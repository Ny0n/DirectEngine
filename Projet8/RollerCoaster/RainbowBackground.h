#pragma once

#include "EngineLib.h"

class RainbowBackground : public Component
{

public:
	const char* GetType() override { return NAMEOF(RainbowBackground); }
	ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }
	
	void Update(float runTime, float deltaTime) override;
	
};
