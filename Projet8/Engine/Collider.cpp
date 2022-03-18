#include "pch.h"

bool Collider::IsColliding(Collider* other)
{
	D3DXVECTOR3 thisPos = transform->GetPosition();
	D3DXVECTOR3 otherPos = other->transform->GetPosition();
	if(Utils::DistanceWithOutSquareRoot(thisPos, otherPos) < transform->GetScale().x * other->transform->GetScale().x)
	{
		return true;
	}
	return false;
}
