#pragma once

class Camera final : public EngineComponent
{
    string GetType() override { return NAMEOF(Camera); }

    void EngineStart() override;
    void EngineUpdate() override;

public:
    void ChangeFVP(float newFVP);
    void ChangeNVP(float newNVP);
    void ChangeSkyColor(D3DCOLOR skyColor);

private:
    float _nvp = 1.0f; // the near view-plane
    float _fvp = 1000.0f; // the far view-plane

    D3DCOLOR _skyColor = D3DCOLOR_XRGB(0, 0, 0); // light-blue background
};
