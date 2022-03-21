#pragma once

class Camera : public Component
{

public:
	const char* GetType() override { return NAMEOF(Camera); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }

    void Start() override;
    void Update() override;

    void ChangeFVP(float newFVP);
    void ChangeNVP(float newNVP);

private:
    float nvp = 1.0f; // the near view-plane
    float fvp = 1000.0f; // the far view-plane
};
