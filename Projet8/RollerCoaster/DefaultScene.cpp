#include "DefaultScene.h"

#include "Cube.h"
#include "DontDestroyOnLoad.h"
#include "GoUp.h"
#include "FPCam.h"
#include "InputTester.h"
#include "Move.h"
#include "MoveAlongRails.h"
#include "RailMaker.h"
#include "RainbowBackground.h"
#include "Rotate.h"

string DefaultScene::GetName()
{
	return "DefaultScene";
}

void DefaultScene::GenerateContent()
{
	// tests

	GameObject* inputTester = CreateEmpty();
	inputTester->AddComponent<InputTester>();
	AddToScene(inputTester);

	// rgb background

	GameObject* rgb = CreateEmpty();
	rgb->AddComponent<RainbowBackground>();
	AddToScene(rgb);

	GameObject* aligneBox = CreateEmpty();
	aligneBox->AddComponent<AlignedBox>();
	AddToScene(aligneBox);

	// camera

	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	mainCamera->AddComponent(new FPCam());
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent<RailMaker>();
	mainCamera->AddComponent<MoveAlongRails>();
	AddToScene(mainCamera);

	// cube

	GameObject* cube1 = CreateEmpty();
	cube1->AddComponent<Cube>();
	cube1->AddComponent<Move>();
	cube1->AddComponent<Collider>();
	cube1->AddComponent<Rotate>(150.0f, true);
	// cube1->AddComponent<DontDestroyOnLoad>();

	cube1->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	cube1->transform->Rotate(40, -40, 0);

	AddToScene(cube1);

	GameObject* cube2 = CreateEmpty();
	cube2->AddComponent<Cube>();
	cube2->AddComponent<Collider>();
	cube2->AddComponent<Rotate>(150.0f);

	cube2->transform->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	cube2->transform->Rotate(40, 40, 0);

	AddToScene(cube2);

	// tigre

	GameObject* tigre = CreateEmpty();

	LPCWSTR path = L"Mesh\\cube.x";
	tigre->AddComponent<MeshRenderer>(path);
	//tigre->AddComponent<Move>();
	tigre->AddComponent<Collider>();
	// tigre->AddComponent<GoUp>(8);
	tigre->AddComponent<Rotate>();

	tigre->transform->SetPosition(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	tigre->transform->RotateYaw(22);
	tigre->transform->SetScale(tigre->transform->GetScale() * 0.01f);

	AddToScene(tigre);
}
