#include "FPCam.h"

#include "MoveAlongRails.h"

class MoveAlongRails;

FPCam::FPCam(float speed) : _speed(speed)
{

}

// **************************** //

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

  //  yaw += (mouseP.x - SCREEN_WIDTH / 2)/100.0f * sensibility * Time::deltaTime;
//
}

void FPCam::LateUpdate()
{

    Transform tmp = static_cast<Transform>(gameObject->GetComponent<MoveAlongRails>()->GetTransfromWhithoutCursor());


    D3DXVECTOR3 tmpPos = tmp.GetPosition();
    D3DXQUATERNION tmpQuat = tmp.GetQuaternion();

    transform->SetPosition(tmpPos);
    transform->SetQuaternion(tmpQuat);

    D3DXVECTOR3 pos = cart->transform->GetPosition();
    pos += cart->transform->GetUp() * 2.0f;
    cart->transform->SetPosition(pos);

    cart->transform->SetPosition(tmpPos);
    cart->transform->SetQuaternion(tmpQuat);
    
    cart->transform->RotateYaw(180); // temp before changing the .x file
    D3DXVECTOR3 cartPos = cart->transform->GetPosition();
    cartPos += -cart->transform->GetUp() * 3.5f;

    cart->transform->SetPosition(cartPos);

    transform->RotatePitch(upSpeed);
    transform->RotateYaw(rightSpeed);
//    transform->RotateYaw(yaw, Space::Self);
   // transform->RotateYaw(3.5f, Space::Self);
    //transform->RotateYaw(-45.0f, Space::Self);

}
