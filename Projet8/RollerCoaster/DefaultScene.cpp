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



	// camera

	GameObject* mainCamera = CreateEmpty();
	auto cam = mainCamera->AddComponent<Camera>();
	cam->ChangeNVP(0.0f);

	auto FpCamCompo = mainCamera->AddComponent<FPCam>();

	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent<RailMaker>();
	mainCamera->AddComponent<MoveAlongRails>();
	AddToScene(mainCamera);

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

	//cart

	GameObject* cart = CreateEmpty();

	LPCWSTR cartPath = L"Mesh\\minecart.x";
	cart->AddComponent<MeshRenderer>(cartPath);


	AddToScene(cart);

	FpCamCompo->SetCart(cart);

}
