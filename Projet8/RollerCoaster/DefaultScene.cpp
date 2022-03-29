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
	Cursor::Lock();
	Cursor::SetVisible(false);

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
	auto cam = mainCamera->AddComponent<FPCam>();
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent<RailMaker>();
	mainCamera->AddComponent<MoveAlongRails>();
	AddToScene(mainCamera);
	GameObject* cart = CreateEmpty();

	LPCWSTR cartPath = L"Mesh\\tiger.x";
	//cart->AddComponent<MeshRenderer>(cartPath);
	cart->AddComponent<MeshRenderer>(L"Mesh\\tiger.x");


	AddToScene(cart);

	cam->SetCart(cart);


	// cube

	
}
