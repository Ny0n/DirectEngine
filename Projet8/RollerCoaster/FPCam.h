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

	void SetCart(GameObject* newCart) { _pCart = newCart; }

	void SetParticle(GameObject* newParticle) { _pParticle = newParticle; }
private:
	float _speed{ 10.0f };

	float _rightSpeed;
	float _upSpeed;
	float _upSpeedLimit = 30.0f;
	
	GameObject* _pCart;
	GameObject* _pParticle;
};
