#include "RainbowBackground.h"

RainbowBackground::RainbowBackground()
{
    type = ComponentType::movable_cube;
}

unsigned __int8 r = 0;
unsigned __int8 g = 0;
unsigned __int8 b = 0;

void RainbowBackground::Update(float runTime, float deltaTime)
{
    if (r == 255 && g == 255 && b == 255)
    {
        r = 0;
        g = 0;
        b = 0;
    }

    if (r < 255)
        r++;
    else if (g < 255)
        g++;
    else if (b < 255)
        b++;

    // clear the window to a deep blue
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
}
