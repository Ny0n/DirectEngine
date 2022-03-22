#pragma once

#include "EngineLib.h"

class InputRotate : public MonoBehaviour
{
public:
	const char* GetType() override { return NAMEOF(InputRotate); }

	InputRotate() = default;
	explicit InputRotate(float speed);

	void Update() override;

private:
	float _speed{ 10.0f };
	float oldPosX;
	float oldPosY;
};
