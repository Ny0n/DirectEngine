#include "LionelScene.h"

#include "FPCam.h"
#include "InputTester.h"
#include "Move.h"
#include "Shoot.h"

string LionelScene::GetName()
{
	return "LionelScene";
}

void LionelScene::GenerateContent()
{
	//collider
	GameObject* aligneBox = CreateEmpty();
	aligneBox->AddComponent<AlignedBox>();
	AddToScene(aligneBox);


	// Camera
	GameObject* Camera = CreateEmpty();

	//Camera Data
	Camera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -60.0f));

	// Camera Component
	Camera->AddComponent<class Camera>();
	Camera->AddComponent<FPCam>();
	Camera->AddComponent<InputTester>();
	Camera->AddComponent<Move>();
	Camera->AddComponent<Shoot>();

	AddToScene(Camera);

	// Sphere

	GameObject* enorme = CreateEmpty();

	LPCWSTR path2 = L"Mesh\\rail.x";
	enorme->AddComponent<MeshRenderer>(path2);
	enorme->AddComponent<Collider>();

	enorme->transform->SetPosition(D3DXVECTOR3(30.0f, 0.0f, 0.0f));

	AddToScene(enorme);

	// Sphere

	GameObject* Sphere = CreateEmpty();

	LPCWSTR path = L"Mesh\\minecart.x";
	Sphere->AddComponent<MeshRenderer>(path);
	Sphere->AddComponent<Collider>();

	AddToScene(Sphere);

}
