#pragma once

#include "EngineLib.h"

class RainbowBackground : public Component
{

public:
	ComponentType GetType() override { return ComponentType::mono_behaviour; }
	
	void Update(float runTime, float deltaTime) override;

};
