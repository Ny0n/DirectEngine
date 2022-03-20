#pragma once

#include "EngineLib.h"

class InputTester : public Component
{

public:
	const char* GetType() override { return NAMEOF(InputTester); }
	ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	void Start() override;
	void Update() override;
	void FixedUpdate() override;
};
