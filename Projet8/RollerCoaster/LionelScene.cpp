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

	GameObject* Sphere = CreateEmpty();

	LPCWSTR path = L"Mesh\\sphere.x";
	Sphere->AddComponent<MeshRenderer>(path);

	AddToScene(Sphere);

}
