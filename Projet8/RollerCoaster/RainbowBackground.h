#pragma once

#include "EngineLib.h"

class RainbowBackground : public MonoBehaviour
{

public:
	const char* GetType() override { return NAMEOF(RainbowBackground); }
	
	void Update() override;
	
};
