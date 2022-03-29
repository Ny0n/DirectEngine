#include "FPCam.h"

#include "MoveAlongRails.h"

class MoveAlongRails;

FPCam::FPCam(float speed) : _speed(speed)
{

}

// **************************** //

void FPCam::Start()
{
    upSpeed = 0;
    rightSpeed = 0;
}

void FPCam::Update()
{


    POINT mouseP;
    float sensibility = 5.0f;
    GetCursorPos(&mouseP);

    if (Input::GetKey(KeyCode::Z) && upSpeed > -70)
        upSpeed -=1;
    if (Input::GetKey(KeyCode::S) && upSpeed < 180)
        upSpeed += 1;
    if (Input::GetKey(KeyCode::Q))
        rightSpeed -= 1;
    if (Input::GetKey(KeyCode::D) )
        rightSpeed+= 1;

    rightSpeed += (mouseP.x - SCREEN_WIDTH / 2) / 100.0f * sensibility;
    upSpeed += (mouseP.y - SCREEN_HEIGHT / 2) / 100.0f * sensibility;
    if (upSpeed < -upSpeedLimit)
        upSpeed = -upSpeedLimit;
    if (upSpeed > upSpeedLimit)
        upSpeed = upSpeedLimit;

    
}

void FPCam::LateUpdate()
{
	auto* mar = gameObject->GetComponent<MoveAlongRails>();

    D3DXVECTOR3 tmpPos;
    D3DXQUATERNION tmpQuat = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
    if( mar != nullptr )
    {
	    const Transform* tmp = mar->GetTransfromWhithoutCursor();
        transform->SetPosition(tmp->GetPosition());
        transform->SetQuaternion(tmp->GetQuaternion());
        transform->SetCustomAxis(tmp->GetRight(), tmp->GetUp(), tmp->GetForward());
        tmpPos = tmp->GetPosition();
        tmpQuat = tmp->GetQuaternion();
    }
    
    transform->RotatePitch(upSpeed, Space::Self);
    transform->RotateYaw(rightSpeed, Space::Custom);
    cart->transform->SetPosition(tmpPos);
    cart->transform->SetQuaternion(tmpQuat);

    cart->transform->RotateYaw(180); // temp before changing the .x file
    D3DXVECTOR3 cartPos = cart->transform->GetPosition();
    cartPos += -cart->transform->GetUp() * 3.5f;
    cartPos += cart->transform->GetForward() * 1;

    cart->transform->SetPosition(cartPos);
}
