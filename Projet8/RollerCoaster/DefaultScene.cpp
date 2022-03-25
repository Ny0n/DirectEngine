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
	inputTester->AddComponent(new InputTester());
	AddToScene(inputTester);

	// rgb background

	GameObject* rgb = CreateEmpty();
	rgb->AddComponent(new RainbowBackground());
	AddToScene(rgb);

	GameObject* aligneBox = CreateEmpty();
	aligneBox->AddComponent(new AlignedBox());
	AddToScene(aligneBox);
	// camera

	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	mainCamera->AddComponent(new FPCam());
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent(new RailMaker());
	mainCamera->AddComponent(new MoveAlongRails());
	AddToScene(mainCamera);

	// cube

	GameObject* cube1 = CreateEmpty();
	cube1->AddComponent(new Cube());
	cube1->AddComponent(new Move());
	cube1->AddComponent(new DontDestroyOnLoad());
	cube1->AddComponent(new Collider);
	cube1->AddComponent(new Rotate(150.0f, true));

	cube1->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	cube1->transform->Rotate(40, -40, 0);

	AddToScene(cube1);

	GameObject* cube2 = CreateEmpty();
	cube2->AddComponent(new Cube());
	cube2->AddComponent(new Collider);
	cube2->AddComponent(new Rotate(150.0f));

	cube2->transform->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	cube2->transform->Rotate(40, 40, 0);

	AddToScene(cube2);

	// tigre

	GameObject* tigre = CreateEmpty();

	LPCWSTR path = L"Mesh\\cube.x";
	tigre->AddComponent(new MeshRenderer(path));
	//tigre->AddComponent(new Move());
	tigre->AddComponent(new Collider);
	// tigre->AddComponent(new GoUp(8));
	tigre->AddComponent(new Rotate());

	tigre->transform->SetPosition(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	tigre->transform->RotateYaw(22);
	tigre->transform->SetScale(tigre->transform->GetScale() * 0.01f);

	AddToScene(tigre);
}
