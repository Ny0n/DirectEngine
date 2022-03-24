#pragma once

#include "EngineLib.h"

class BulletMove : public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(BulletMove); }
	void Start() override;
	void Update() override;

	void SetBulletSpeed(float speed) { bulletSpeed = speed; }
	void SetmaxTimer(float time) { maxTimer = time; }

private:
	float bulletSpeed = 10.0f;
	float maxTimer = 5.0f; //time before destroy
	float currentTimer;
};
