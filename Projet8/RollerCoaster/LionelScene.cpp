#include "LionelScene.h"

#include "GoUp.h"
#include "InputTester.h"
#include "Move.h"
#include "RealFPCam.h"
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
	Camera->AddComponent<RealFPCam>();
	Camera->AddComponent<InputTester>();
	Camera->AddComponent<Move>();
	Camera->AddComponent<Shoot>();

	AddToScene(Camera);

	// Sphere

	GameObject* Sphere = CreateEmpty();

	LPCWSTR path = L"Mesh\\minecart.x";
	Sphere->AddComponent<MeshRenderer>(path);
	Sphere->AddComponent<Collider>();
	Sphere->AddComponent<GoUp>();

	Sphere->transform->RotateRoll(45);

	AddToScene(Sphere);

}
