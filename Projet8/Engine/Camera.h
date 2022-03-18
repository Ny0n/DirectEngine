#pragma once

class Camera : public Component
{

public:
	const char* GetType() override { return NAMEOF(Camera); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }

    void Start() override;
    void Update(float runTime, float deltaTime) override;

};
