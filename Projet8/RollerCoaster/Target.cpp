#include "Target.h"

void Target::removeSelf()
{
	_listGameObject->remove(gameObject);
}

void Target::Update()
{
	if(_LookAt != nullptr)
	{
		D3DXVECTOR3 directionForward = transform->GetPosition() - _LookAt->GetPosition();

		D3DXVec3Normalize(&directionForward, &directionForward);
		
		D3DXVECTOR3 directionUp = _LookAt->GetUp();
		D3DXVECTOR3 directionRight;

		D3DXVec3Cross(&directionRight, &directionForward, &directionUp);

		transform->SetRotationFromVectors(&directionRight, &directionUp , &directionForward);
	}
}
