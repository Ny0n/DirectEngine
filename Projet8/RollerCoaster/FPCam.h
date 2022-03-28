#pragma once

#include "EngineLib.h"

class FPCam : public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(FPCam); }

	FPCam() = default;
	explicit FPCam(float speed);

	void Start() override;
	void LateUpdate() override;
	void Update() override;
private:
	float _speed{ 10.0f };

	float rightSpeed;
	float upSpeed;
	float yaw;
};
