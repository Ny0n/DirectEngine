#pragma once

#include "EngineLib.h"

class Move : public MonoBehaviour
{

public:
	const char* GetType() override { return NAMEOF(Move); }

	Move() = default;
	explicit Move(float speed);

	void Update() override;

private:
	float _speed{ 10.0f };

};
