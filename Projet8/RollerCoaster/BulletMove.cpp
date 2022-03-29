#include "BulletMove.h"

#include "Target.h"


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
	transform->RotateRoll(-600.0f * Time::deltaTime);

	if(currentTimer < 0)
	{
		Destroy(gameObject); // throw an exception :/
	}else
	{
		currentTimer -= Time::deltaTime;
	}

}

void BulletMove::OnTriggerEnter(GameObject* collide)
{
	auto t =collide->GetComponent<Target>();
	if (t != nullptr)
		t->removeSelf();
	Destroy(collide);
	//collide->gameObject->Destroy();
}
