#include "RainbowBackground.h"

D3DXVECTOR3 va = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
D3DXVECTOR3 vb = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
D3DXVECTOR3 vc = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
D3DXVECTOR3 vd = D3DXVECTOR3(0.00f, 0.33f, 0.67f);

D3DXVECTOR3 palette(float t, D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 d)
{
    float rR = a.x + b.x * cos(6.28318f * (c.x * t + d.x));
    float rG = a.y + b.y * cos(6.28318f * (c.y * t + d.y));
    float rB = a.z + b.z * cos(6.28318f * (c.z * t + d.z));

    D3DXVECTOR3 result = D3DXVECTOR3(rR, rG, rB);
    return result;
}

float speed = 0.2f;
float progress = 0.0f;

void RainbowBackground::Update()
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(80, 140, 220), 1.0f, 0); // light-blue background
    return;

    D3DXVECTOR3 result = palette(progress, va, vb, vc, vd) * 255.0f;
    progress += speed * Time::deltaTime;

    while (progress >= 1.0f)
        progress -= 1.0f;

    float r = result.x;
    float g = result.y;
    float b = result.z;
    
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b)), 1.0f, 0);
}
