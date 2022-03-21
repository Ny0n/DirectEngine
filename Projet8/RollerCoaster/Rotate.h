#pragma once

#include "EngineLib.h"

class Rotate : public MonoBehaviour
{

public:
	const char* GetType() override { return NAMEOF(Rotate); }

	Rotate() = default;
	explicit Rotate(float speed);
	explicit Rotate(bool reverse);
	Rotate(float speed, bool reverse);

	void Update() override;

private:
	float _speed{ 50.0f };
	float _dir{ 1.0f };

};
