#include "Shoot.h"

#include "BulletMove.h"
#include "Cube.h"

void Shoot::Start()
{

}

void Shoot::Update()
{
	bool shoot = false;

	if(Input::GetKeyDown(KeyCode::Mouse0))
	{
		shoot = true;
	}

	if(shoot == true)
	{
		Utils::Println("Shot");
		GameObject* bullet = new GameObject();
		bullet->transform->SetQuaternion(transform->GetQuaternion());
		bullet->transform->SetPosition(transform->GetPosition());

		LPCWSTR path = L"Mesh\\sphere.x";
		bullet->AddComponent<MeshRenderer>(path);

		auto bulletMove = bullet->AddComponent<BulletMove>();

		bulletMove->SetBulletSpeed(25.0f);


		SceneManager::Instantiate(bullet);
	}
}
