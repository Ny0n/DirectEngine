#include "MenuScene.h"

#include "CECIESTUNSCRIPT.h"
#include "InputTester.h"

string MenuScene::GetName()
{
	return "MenuScene";
}

void MenuScene::GenerateContent()
{
	// tests

	GameObject* inputTester = CreateEmpty();
	inputTester->AddComponent<InputTester>();
	AddToScene(inputTester);

	// camera

	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent<Camera>();
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	AddToScene(mainCamera);

	// canvas

	GameObject* canvas = CreateEmpty();

	// const auto image = canvas->AddComponent<Image>();
	// image->width = 200;
	// image->height = 200;
	// image->filePath = L"Image\\smiley.png";
	//
	// canvas->AddComponent<CECIESTUNSCRIPT>(image);

	canvas->AddComponent<Textbox>(L"Test");

	AddToScene(canvas);
}
