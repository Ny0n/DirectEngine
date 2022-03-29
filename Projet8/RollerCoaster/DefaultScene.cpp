#include "DefaultScene.h"

#include "CrosshairScript.h"
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
	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	auto cam = mainCamera->AddComponent<FPCam>();
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent<RailMaker>();
	mainCamera->AddComponent<MoveAlongRails>();
	AddToScene(mainCamera);
	GameObject* inputTester = CreateEmpty();
	inputTester->AddComponent<InputTester>();
	AddToScene(inputTester);

	//cart
	GameObject* cart = CreateEmpty();

	LPCWSTR cartPath = L"Mesh\\tiger.x";
	//cart->AddComponent<MeshRenderer>(cartPath);
	cart->AddComponent<MeshRenderer>(L"Mesh\\tiger.x");

	AddToScene(cart);

	cam->SetCart(cart);


	// crosshair
	auto crossGO = CreateEmpty();
	auto img = crossGO->AddComponent<Image>();

	img->filePath = L"Image\\flavien3.png";
	img->position = D3DXVECTOR2(SCREEN_WIDTH * .5f, SCREEN_HEIGHT * .5f);
	img->originalSize = true;
	//img->scale = D3DXVECTOR2(.1f, .1f);
	img->scale = D3DXVECTOR2(.5f, .5f);
	img->imageColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	img->drawFromCenter = true;

	crossGO->AddComponent<CrosshairScript>(img);

	AddToScene(crossGO);
	
	//
}
