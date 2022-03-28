#pragma once

#include "EngineLib.h"

class Move : public MonoBehaviour
{
	string GetType() override { return NAMEOF(Move); }

	void Start() override;
	void Update() override;

public:
	Move() = default;
	explicit Move(float speed);
	
	float speed{ 10.0f };

};
