#include "GoUp.h"

GoUp::GoUp(float speed) : _speed(speed)
{
}

// **************************** //

void GoUp::Update(float runTime, float deltaTime)
{
    D3DXVECTOR3 pos = transform->GetPosition();
    pos.y += _speed * deltaTime;
    transform->SetPosition(pos);
}
