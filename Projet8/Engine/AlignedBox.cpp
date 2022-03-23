#include "pch.h"

void AlignedBox::EngineStart()
{
	colliders = {};
	transform->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
}

list<Collider*> AlignedBox::AreIn(const list<GameObject*> go)
{
	colliders.clear();
	const D3DXVECTOR3 pos = transform->GetPosition();
	const D3DXVECTOR3 scale = transform->GetScale();
	for(GameObject* g : go)
	{
		D3DXVECTOR3 tmpPos = g->transform->GetPosition();
		auto collider = g->GetComponent<Collider>();
		if (collider != nullptr
			&& pos.x - scale.x<= tmpPos.x && pos.x + scale.x>=tmpPos.x
			&& pos.y - scale.y<= tmpPos.y && pos.y + scale.y>=tmpPos.y
			&& pos.z - scale.z<= tmpPos.z && pos.z + scale.z>=tmpPos.z)
		{
			colliders.push_back(collider);
		}
	}
	return colliders;
}
