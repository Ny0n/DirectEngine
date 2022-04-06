#include "pch.h"

Collider::Collider()
{
	_collidersWith = {};
}

Collider::~Collider()
{
	_collidersWith.clear();
}

bool Collider::IsColliding(Collider* other)
{
	D3DXVECTOR3 thisPos = transform->GetPosition();
	D3DXVECTOR3 otherPos = other->transform->GetPosition();
	if(Utils::DistanceWithOutSquareRoot(thisPos, otherPos) < transform->GetScale().x + other->transform->GetScale().x* transform->GetScale().x + other->transform->GetScale().x)
	{
		return true;
	}
	return false;
}

void Collider::RemoveCollideWith(Collider* collide)
{
	if (Utils::Contains(&_collidersWith, collide))
		_collidersWith.remove(collide);
}
