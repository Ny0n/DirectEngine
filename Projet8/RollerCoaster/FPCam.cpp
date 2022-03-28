#include "FPCam.h"

#include "MoveAlongRails.h"

class MoveAlongRails;

FPCam::FPCam(float speed) : _speed(speed)
{

}


void FPCam::Start()
{
    Cursor::SetVisible(TRUE);
    //Cursor::Lock();
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
    Utils::Println(upSpeed);
  //  yaw += (mouseP.x - SCREEN_WIDTH / 2)/100.0f * sensibility * Time::deltaTime;
//
}

void FPCam::LateUpdate()
{

    Transform tmp = static_cast<Transform>(gameObject->GetComponent<MoveAlongRails>()->GetTransfromWhithoutCursor());
    transform->SetPosition(tmp.GetPosition());
    transform->SetQuaternion(tmp.GetQuaternion());
    transform->RotatePitch(upSpeed, Space::Self);
    transform->RotateYaw(rightSpeed, Space::Self);
//    transform->RotateYaw(yaw, Space::Self);
   // transform->RotateYaw(3.5f, Space::Self);
    //transform->RotateYaw(-45.0f, Space::Self);

}
