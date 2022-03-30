#include "Target.h"

void Target::removeSelf()
{
	_pListGameObject->remove(gameObject);
}

void Target::Update()
{
	if(_pLookAt != nullptr)
	{
		D3DXVECTOR3 directionForward = transform->GetPosition() - _pLookAt->GetPosition();

		D3DXVec3Normalize(&directionForward, &directionForward);
		
		D3DXVECTOR3 directionUp = _pLookAt->GetUp();
		D3DXVECTOR3 directionRight;

		D3DXVec3Cross(&directionRight, &directionForward, &directionUp);

		transform->SetRotationFromVectors(&directionRight, &directionUp , &directionForward);
	}
}
