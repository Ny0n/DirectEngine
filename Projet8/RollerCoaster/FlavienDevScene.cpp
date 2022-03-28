#include "FlavienDevScene.h"

#include "Cube.h"
#include "InputTester.h"
#include "Move.h"
#include "Rotate.h"
#include "Tester.h"

string FlavienDevScene::GetName()
{
	return "FlavienDevScene";
}

void FlavienDevScene::GenerateContent()
{
	Cursor::Unlock();
	Cursor::SetVisible(true);

	// camera
	
	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent<Camera>();
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	AddToScene(mainCamera);
	
	// tests
	
	GameObject* tester = CreateEmpty();

	tester->AddComponent<InputTester>();
	tester->AddComponent<Move>();
	tester->AddComponent<Cube>();
	tester->AddComponent<Rotate>(150.0f, true);
	auto x = tester->AddComponent<Tester>();
	x->SetEnabled(true);
	// Utils::Println("hey");
	tester->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	tester->transform->Rotate(40, -40, 0);

	AddToScene(tester);

	// // monkey
	//
	// GameObject* monkey = CreateEmpty();
	//
	// LPCWSTR path = L"Mesh\\monkey.x";
	// monkey->AddComponent<MeshRenderer>(path);
	// monkey->AddComponent<Collider>();
	//
	// monkey->transform->SetPosition(D3DXVECTOR3(-5.0f, -5.0f, 0.0f));
	// monkey->transform->RotateYaw(22);
	// monkey->transform->SetScale(monkey->transform->GetScale() * 0.05f);
	//
	// AddToScene(monkey);
}
