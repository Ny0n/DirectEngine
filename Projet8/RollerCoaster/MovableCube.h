#pragma once

#include "Component.h"

class MovableCube : public Component
{

public:
	MovableCube();

	void Update(float runTime, float deltaTime) override;

};
