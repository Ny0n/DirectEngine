#include "FlavienDevScene.h"

#include "Cube.h"
#include "InputTester.h"
#include "Move.h"
#include "Rotate.h"

string FlavienDevScene::GetName()
{
	return "FlavienDevScene";
}

void FlavienDevScene::GenerateContent()
{
	// camera
	
	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	AddToScene(mainCamera);
	
	// tests
	
	GameObject* tester = CreateEmpty();
	tester->AddComponent(new InputTester());
	tester->AddComponent(new Move());
	tester->AddComponent(new Cube());
	tester->AddComponent(new Rotate(150.0f, true));

	tester->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	tester->transform->Rotate(40, -40, 0);

	AddToScene(tester);

	// // monkey
	//
	// GameObject* monkey = CreateEmpty();
	//
	// LPCWSTR path = L"Mesh\\monkey.x";
	// monkey->AddComponent(new MeshRenderer(path));
	// monkey->AddComponent(new Collider);
	//
	// monkey->transform->SetPosition(D3DXVECTOR3(-5.0f, -5.0f, 0.0f));
	// monkey->transform->RotateYaw(22);
	// monkey->transform->SetScale(monkey->transform->GetScale() * 0.05f);
	//
	// AddToScene(monkey);
}
