#pragma once

#include "EngineLib.h"

class GoUp : public MonoBehaviour
{
	string GetType() override { return NAMEOF(GoUp); }

	void Start() override;
	void Update() override;

public:
	GoUp() = default;
	explicit GoUp(float speed);

private:
	float _speed{ 1.0f };

};
