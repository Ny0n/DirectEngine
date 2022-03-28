#pragma once

class Camera final : public EngineComponent
{
    string GetType() override { return NAMEOF(Camera); }

    void EngineStart() override;
    void EngineUpdate() override;

public:
    void ChangeFVP(float newFVP);
    void ChangeNVP(float newNVP);

private:
    float nvp = 1.0f; // the near view-plane
    float fvp = 1000.0f; // the far view-plane

};
