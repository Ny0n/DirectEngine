#include "RealFPCam.h"


// Start is called before the first frame update
void RealFPCam::Start()
{
    Cursor::Lock();
    Cursor::SetVisible(false);
}

// Update is called once per frame
void RealFPCam::Update()
{
    POINT mouseP;
    float sensibility = 7.0f;
    GetCursorPos(&mouseP);

    float upSpeed = (mouseP.y - SCREEN_HEIGHT / 2) * sensibility * Time::deltaTime;
    float rightSpeed = (mouseP.x - SCREEN_WIDTH / 2) * sensibility * Time::deltaTime;

    // Utils::Println(upSpeed);

    transform->RotatePitch(upSpeed);
    transform->RotateYaw(rightSpeed, Space::World);
}
