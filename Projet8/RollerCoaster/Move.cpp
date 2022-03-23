#include "Move.h"

Move::Move(float speed) : speed(speed)
{
}

// **************************** //

void Move::Update()
{
    // we get the movement vector

    D3DXVECTOR3 movement = D3DXVECTOR3(0, 0, 0);

    if (Input::GetKey(KeyCode::Z))
        movement.y += 1;
    if (Input::GetKey(KeyCode::S))
        movement.y += -1;
    if (Input::GetKey(KeyCode::Q))
        movement.x += -1;
    if (Input::GetKey(KeyCode::D))
        movement.x += 1;

    D3DXVec3Normalize(&movement, &movement); // so that we don't go faster in diagonals

    // and we apply it to the transform's position

    D3DXVECTOR3 pos = transform->GetPosition();
    pos += movement * speed * Time::deltaTime;

    transform->SetPosition(pos);
}
