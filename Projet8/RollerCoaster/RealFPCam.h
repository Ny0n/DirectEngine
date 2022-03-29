#pragma once

#include "EngineLib.h"

class RealFPCam : public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(RealFPCam); }
	void Start() override;
	void Update() override;
	
};
