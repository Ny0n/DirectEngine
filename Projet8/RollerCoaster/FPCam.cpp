#include "FPCam.h"

FPCam::FPCam(float speed) : _speed(speed)
{
    
}

// **************************** //

void FPCam::Start()
{
    Cursor::Lock();
    Cursor::SetVisible(false);
}

void FPCam::Update()
{
    float sensibility = 10.0f;

    POINT mouseP;

    GetCursorPos(&mouseP);

    float rightSpeed = (mouseP.x - SCREEN_WIDTH / 2);
    float upSpeed = (mouseP.y - SCREEN_HEIGHT / 2);

    //Utils::Println(centerX);

    transform->RotatePitch(upSpeed * sensibility * Time::deltaTime);
    transform->RotateYaw(rightSpeed * sensibility * Time::deltaTime, Space::World);
}
