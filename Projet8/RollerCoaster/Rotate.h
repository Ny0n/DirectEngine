#pragma once

#include "EngineLib.h"

class Rotate : public Component
{

public:
	const char* GetType() override { return NAMEOF(Rotate); }
	ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	Rotate() = default;
	explicit Rotate(float speed);
	explicit Rotate(bool reverse);
	Rotate(float speed, bool reverse);

	void Update() override;

private:
	float _speed{ 50.0f };
	float _dir{ 1.0f };

};
