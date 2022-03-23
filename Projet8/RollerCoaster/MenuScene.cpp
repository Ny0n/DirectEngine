#include "MenuScene.h"

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

	// monkey

	GameObject* monkey = CreateEmpty();

	LPCWSTR path = L"Mesh\\monkey.x";
	monkey->AddComponent(new MeshRenderer(path));
	monkey->AddComponent(new Collider);

	monkey->transform->SetPosition(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	monkey->transform->RotateYaw(22);
	monkey->transform->SetScale(monkey->transform->GetScale() * 0.05f);

	AddToScene(monkey);
}
