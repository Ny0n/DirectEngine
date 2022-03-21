#pragma once

class Camera final : public EngineComponent
{

public:
	const char* GetType() override { return NAMEOF(Camera); }
    
    void EngineStart() override;
    void EngineUpdate() override;

    void ChangeFVP(float newFVP);
    void ChangeNVP(float newNVP);

private:
    float nvp = 1.0f; // the near view-plane
    float fvp = 1000.0f; // the far view-plane
};
