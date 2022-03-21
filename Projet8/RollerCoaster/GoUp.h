#pragma once

#include "EngineLib.h"

class GoUp : public MonoBehaviour
{

public:
	const char* GetType() override { return NAMEOF(GoUp); }

	GoUp() = default;
	explicit GoUp(float speed);

	void Update() override;

private:
	float _speed{ 1.0f };

};
