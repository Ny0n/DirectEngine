#pragma once

class Camera final : public EngineComponent
{

public:
	string GetType() override { return NAMEOF(Camera); }
    
    void EngineStart() override;
    void EngineUpdate() override;

    void ChangeFVP(float newFVP);
    void ChangeNVP(float newNVP);
    void ChangeSkyColor(D3DCOLOR skyColor);

private:
    float nvp = 1.0f; // the near view-plane
    float fvp = 1000.0f; // the far view-plane

    D3DCOLOR skyColor = D3DCOLOR_XRGB(80, 140, 220); // light-blue background
};
