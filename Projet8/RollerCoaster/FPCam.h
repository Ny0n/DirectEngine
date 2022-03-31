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
	void SetParticle(GameObject* newParticle) { _particle = newParticle; }

private:
	float _speed{ 10.0f };

	float rightSpeed;
	float upSpeed;
	float upSpeedLimit = 30.0f;
	GameObject* cart;
	GameObject* _particle;
};
