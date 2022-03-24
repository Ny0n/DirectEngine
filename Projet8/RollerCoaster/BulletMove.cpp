#include "BulletMove.h"


// Start is called before the first frame update
void BulletMove::Start()
{
	currentTimer = maxTimer;
}

// Update is called once per frame
void BulletMove::Update()
{
	auto dir = transform->GetForward();

	D3DXVECTOR3 pos = transform->GetPosition();
	pos += dir * bulletSpeed * Time::deltaTime;

	transform->SetPosition(pos);

	if(currentTimer < 0)
	{
		//gameObject->Destroy(); // throw an exception :/
	}else
	{
		currentTimer -= Time::deltaTime;
	}

}
