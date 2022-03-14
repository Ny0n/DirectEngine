#pragma once

#include "EngineLib.h"

class RainbowBackground : public Component
{

public:
	RainbowBackground();

	void Start() override;
	void Update(float runTime, float deltaTime) override;

};
