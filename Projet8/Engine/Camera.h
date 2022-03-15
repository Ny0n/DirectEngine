#pragma once

#include "Component.h"

class Camera : public Component
{

public:
	const char* GetType() override { return NAMEOF(Camera); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }

    void Update(float runTime, float deltaTime) override;

};
