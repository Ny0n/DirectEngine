#include "InputRotate.h"

InputRotate::InputRotate(float speed) : _speed(speed)
{
    POINT mouseP;

    GetCursorPos(&mouseP);

    oldPosX = SCREEN_WIDTH / 2;
    oldPosY = SCREEN_HEIGHT / 2;
}

void InputRotate::Update()
{
    float sensibility = 10.0f;

    POINT mouseP;

    GetCursorPos(&mouseP);

    float rightSpeed = (mouseP.x - oldPosX) - SCREEN_WIDTH / 2;
    float upSpeed = (mouseP.y - oldPosY) - SCREEN_HEIGHT / 2;
    


    if (rightSpeed < 0.0f)
        Utils::Println("left");

    if (rightSpeed > 0.0f)
        Utils::Println("right");

    if (upSpeed < 0.0f)
        Utils::Println("up");

    if (upSpeed > 0.0f)
        Utils::Println("down");


    transform->RotatePitch(upSpeed * sensibility * Time::deltaTime);
    transform->RotateYaw(rightSpeed * sensibility * Time::deltaTime);
    
    SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    ShowCursor(false);
}
