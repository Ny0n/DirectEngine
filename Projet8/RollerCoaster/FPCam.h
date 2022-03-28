#pragma once

#include "EngineLib.h"

class FPCam : public MonoBehaviour
{
	string GetType() override { return NAMEOF(FPCam); }

	void Start() override;
	void LateUpdate() override;
	void Update() override;

public:
	FPCam() = default;
	explicit FPCam(float speed);
	void SetCart(GameObject* newCart) { cart = newCart; }

private:
	float _speed{ 10.0f };

	float rightSpeed;
	float upSpeed;
	float yaw;

	GameObject* cart;
};
