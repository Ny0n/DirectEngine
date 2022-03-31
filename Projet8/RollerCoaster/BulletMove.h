#pragma once

#include "EngineLib.h"

class BulletMove : public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(BulletMove); }
	void Start() override;
	void FixedUpdate() override;

	void SetBulletSpeed(float speed) { _bulletSpeed = speed; }
	void SetmaxTimer(float time) { _maxTimer = time; }

	void OnTriggerEnter(GameObject* collide) override;

private:
	float _bulletSpeed = 30.0f; //default bullet speed
	float _maxTimer = 10.0f; //default time before destroy
	float _currentTimer;
};
