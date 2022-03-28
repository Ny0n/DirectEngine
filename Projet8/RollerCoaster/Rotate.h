#pragma once

#include "EngineLib.h"

class Rotate : public MonoBehaviour
{
	string GetType() override { return NAMEOF(Rotate); }

	void Start() override;
	void Update() override;

public:
	Rotate() = default;
	explicit Rotate(float speed);
	explicit Rotate(bool reverse);
	Rotate(float speed, bool reverse);

private:
	float _speed{ 50.0f };
	float _dir{ 1.0f };

};
