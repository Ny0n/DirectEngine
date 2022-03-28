#pragma once

#include "EngineLib.h"

class FPCam : public MonoBehaviour
{
	string GetType() override { return NAMEOF(FPCam); }

	void Start() override;
	void Update() override;

public:
	FPCam() = default;
	explicit FPCam(float speed);

private:
	float _speed{ 10.0f };
	float centerX = 0.0f;
	float centerY = 0.0f;

};
