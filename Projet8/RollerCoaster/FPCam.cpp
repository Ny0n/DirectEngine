#include "FPCam.h"

#include "MoveAlongRails.h"

class MoveAlongRails;

FPCam::FPCam(float speed) : _speed(speed)
{

}

// **************************** //

void FPCam::Start()
{
    yaw = 0.0f;
}

void FPCam::Update()
{

    POINT mouseP;
    float sensibility = 5.0f;
    GetCursorPos(&mouseP);

    if (Input::GetKey(KeyCode::Z) && upSpeed > -90)
        upSpeed -=1;
    if (Input::GetKey(KeyCode::S) && upSpeed < 90)
        upSpeed += 1;
    if (Input::GetKey(KeyCode::Q) && rightSpeed > -90)
        rightSpeed -= 1;
    if (Input::GetKey(KeyCode::D) && rightSpeed < 90)
        rightSpeed+= 1;

    rightSpeed += (mouseP.x - SCREEN_WIDTH / 2) / 100.0f * sensibility;
    upSpeed += (mouseP.y - SCREEN_HEIGHT / 2) / 100.0f * sensibility;
    if (rightSpeed > 90)
        rightSpeed = 90;
    if (rightSpeed < -90)
        rightSpeed = -90;
    if (upSpeed > 90)
        upSpeed = 90;
    if (upSpeed < -90)
        upSpeed = -90;
//
}

void FPCam::LateUpdate()
{
	auto* mar = gameObject->GetComponent<MoveAlongRails>();
    if( mar != nullptr )
    {
	    const Transform* tmp = mar->GetTransfromWhithoutCursor();
        transform->SetPosition(tmp->GetPosition());
        transform->SetQuaternion(tmp->GetQuaternion());
    }
    transform->RotatePitch(upSpeed, Space::Self);
    transform->RotateYaw(rightSpeed, Space::Self);

}
