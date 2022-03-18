#include "pch.h"
void AlignedBox::Start()
{
	colliders ={};
	transform->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
}

void AlignedBox::Update(float runTime, float deltaTime)
{
}

list<GameObject*> AlignedBox::AreIn(list<GameObject*> go)
{
	const D3DXVECTOR3 pos = transform->GetPosition();
	const D3DXVECTOR3 scale = transform->GetScale();
	for(GameObject* g : go)
	{
		D3DXVECTOR3 tmpPos = g->transform->GetPosition();
		if (g->GetComponent(NAMEOF(Collider))
			&& pos.x - scale.x<= tmpPos.x && pos.x + scale.x>=tmpPos.x
			&& pos.y - scale.y<= tmpPos.y && pos.y + scale.y>=tmpPos.y
			&& pos.z - scale.z<= tmpPos.z && pos.z + scale.z>=tmpPos.z)
		{
			colliders.push_back(g);
		}
	}
	return colliders;
}

