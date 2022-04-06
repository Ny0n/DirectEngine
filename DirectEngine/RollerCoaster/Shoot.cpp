#include "Shoot.h"

#include "BulletMove.h"
#include "GameManager.h"

void Shoot::Start()
{

}

void Shoot::Update()
{
	bool shoot = false;

	if(Input::GetKeyDown(KeyCode::Mouse0))
	{
		if (!GameManager::IsPaused())
			shoot = true;
	}

	if(shoot == true)
	{
		GameObject* bullet = new GameObject();
		bullet->transform->SetQuaternion(transform->GetQuaternion());
		bullet->transform->SetPosition(transform->GetPosition());
		bullet->transform->SetScale(bullet->transform->GetScale() * 0.5f);

		LPCWSTR path = L"Mesh\\bullet.x";
		bullet->AddComponent<MeshRenderer>(path);
		bullet->AddComponent<Collider>();

		auto bulletMove = bullet->AddComponent<BulletMove>();

		bulletMove->SetBulletSpeed(100.0f);


		Instantiate(bullet);
	}
}
