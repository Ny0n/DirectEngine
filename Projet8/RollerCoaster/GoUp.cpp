#include "GoUp.h"

GoUp::GoUp(float speed) : _speed(speed)
{
}

// **************************** //

void GoUp::Start()
{
}

void GoUp::Update()
{
    D3DXVECTOR3 pos = transform->GetPosition();
    pos.y += _speed * Time::deltaTime;
    transform->SetPosition(pos);
}
