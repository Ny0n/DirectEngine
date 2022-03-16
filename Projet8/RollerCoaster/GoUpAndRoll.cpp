#include "GoUpAndRoll.h"

void GoUpAndRoll::Update(float runTime, float deltaTime)
{
    D3DXVECTOR3 pos = transform->GetPosition();
    pos.y += 1 * deltaTime;
    transform->SetPosition(pos);
    transform->RotateRoll(50 * deltaTime);
}
