#pragma once

#include "EngineLib.h"

class GoUp : public MonoBehaviour
{

public:
	string GetType() override { return NAMEOF(GoUp); }

	GoUp() = default;
	explicit GoUp(float speed);

	void Update() override;

private:
	float _speed{ 1.0f };

};
