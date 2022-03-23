#pragma once

#include "EngineLib.h"

class RainbowBackground : public MonoBehaviour
{

public:
	string GetType() override { return NAMEOF(RainbowBackground); }
	
	void Update() override;
	
};
