#pragma once

#include "EngineLib.h"

class BulletMove : public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(BulletMove); }
	void Start() override;
	void FixedUpdate() override;

	void SetBulletSpeed(float speed) { bulletSpeed = speed; }
	void SetmaxTimer(float time) { maxTimer = time; }

	void OnTriggerEnter(GameObject* collide) override;

private:
	float bulletSpeed = 30.0f;
	float maxTimer = 10.0f; //time before destroy
	float currentTimer;
};
