#include "RainbowBackground.h"

RainbowBackground::RainbowBackground()
{
    type = ComponentType::movable_cube;
}

void RainbowBackground::Start()
{
}

float r = 0;
float g = 0;
float b = 0;

float speed = 200.0f;

void RainbowBackground::Update(float runTime, float deltaTime)
{
    if (r >= 255 && g >= 255 && b >= 255)
    {
        r = 0;
        g = 0;
        b = 0;
    }

    if (r < 255)
        r += speed * deltaTime;
    else if (g < 255)
        g += speed * deltaTime;
    else if (b < 255)
        b += speed * deltaTime;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    // clear the window to a deep blue
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b)), 1.0f, 0);
}
