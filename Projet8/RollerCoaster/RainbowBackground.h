#pragma once

#include "EngineLib.h"

class RainbowBackground : public MonoBehaviour
{
	string GetType() override { return NAMEOF(RainbowBackground); }

	void Start() override;
	void Update() override;
	
};
