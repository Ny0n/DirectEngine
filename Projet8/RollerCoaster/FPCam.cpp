#include "FPCam.h"

#include "MoveAlongRails.h"

class MoveAlongRails;

FPCam::FPCam(float speed) : _speed(speed)
{
}

// **************************** //

void FPCam::Start()
{
    _upSpeed = 0;
    _rightSpeed = 0;
}

void FPCam::Update()
{
    POINT mouseP;
    float sensibility = 5.0f;
    GetCursorPos(&mouseP);

    if (Input::GetKey(KeyCode::Z) && _upSpeed > -70)
        _upSpeed -=1;
    if (Input::GetKey(KeyCode::S) && _upSpeed < 180)
        _upSpeed += 1;
    if (Input::GetKey(KeyCode::Q))
        _rightSpeed -= 1;
    if (Input::GetKey(KeyCode::D) )
        _rightSpeed+= 1;

    _rightSpeed += (mouseP.x - SCREEN_WIDTH / 2) / 100.0f * sensibility;
    _upSpeed += (mouseP.y - SCREEN_HEIGHT / 2) / 100.0f * sensibility;

    if (_upSpeed < -_upSpeedLimit)
        _upSpeed = -_upSpeedLimit;
    
    if (_upSpeed > _upSpeedLimit)
        _upSpeed = _upSpeedLimit;

    
}

void FPCam::LateUpdate()
{
    MoveAlongRails* moveAlongRails = gameObject->GetComponent<MoveAlongRails>();

    D3DXVECTOR3 tmpPos;
    D3DXQUATERNION tmpQuat = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);

    if(moveAlongRails != nullptr )
    {
        //get the transform without the rotation of the cursor
	    const Transform* tmp = moveAlongRails->GetTransfromWhithoutCursor();
        
        transform->SetPosition(tmp->GetPosition());
        transform->SetQuaternion(tmp->GetQuaternion());
        transform->SetCustomAxis(tmp->GetRight(), tmp->GetUp(), tmp->GetForward());

        tmpPos = tmp->GetPosition();
        tmpQuat = tmp->GetQuaternion();
    }
    
    transform->RotatePitch(_upSpeed, Space::Self);
    transform->RotateYaw(_rightSpeed, Space::Custom);

    _pCart->transform->SetPosition(tmpPos);
    _pCart->transform->SetQuaternion(tmpQuat);
    _particle->transform->SetPosition(tmpPos);

    _pCart->transform->RotateYaw(180); // temp before changing the .x file

    D3DXVECTOR3 cartPos = _pCart->transform->GetPosition();
    cartPos += -_pCart->transform->GetUp() * 3.5f;
    cartPos += _pCart->transform->GetForward() * 1;

    _pCart->transform->SetPosition(cartPos);
}
