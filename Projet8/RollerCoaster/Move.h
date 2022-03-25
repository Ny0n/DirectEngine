#pragma once

#include "EngineLib.h"

class Move : public MonoBehaviour
{

public:
	string GetType() override { return NAMEOF(Move); }

	Move() = default;
	explicit Move(float speed);

	void Update() override;
	
	float speed{ 10.0f };

};
