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
	inputTester->AddComponent(new InputTester());
	AddToScene(inputTester);

	// camera

	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	AddToScene(mainCamera);

	// canvas

	GameObject* canvas = CreateEmpty();

	const auto image = new Image();
	image->width = 200;
	image->height = 200;
	image->filePath = L"C:\\Users\\kperez\\Documents\\direct8\\direct8\\Projet8\\RollerCoaster\\Image\\smiley.png";
	canvas->AddComponent(image);

	auto script = new CECIESTUNSCRIPT(image);
	canvas->AddComponent(script);

	AddToScene(canvas);
}
