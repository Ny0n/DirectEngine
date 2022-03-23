#pragma once

#include "EngineLib.h"

class FPCam : public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(FPCam); }

	FPCam() = default;
	explicit FPCam(float speed);

	void Start() override;
	void Update() override;

private:
	float _speed{ 10.0f };
	float centerX = 0.0f;
	float centerY = 0.0f;
};
