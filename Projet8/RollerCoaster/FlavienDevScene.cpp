#include "FlavienDevScene.h"

#include "AudioTester.h"
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
	auto cam = mainCamera->AddComponent<Camera>();
	cam->ChangeSkyColor(D3DCOLOR_XRGB(0, 0, 0));
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	AddToScene(mainCamera);
	
	// tests
	
	GameObject* tester = CreateEmpty();

	tester->AddComponent<InputTester>();
	// tester->AddComponent<Move>(30.0f);
	tester->AddComponent<Rotate>(150.0f, true);
	tester->AddComponent<MeshRenderer>(L"Mesh\\cube.x");
	tester->transform->SetScale(tester->transform->GetScale() * 0.02f);
	auto x = tester->AddComponent<Tester>();
	x->SetEnabled(true);

	// Utils::Println("hey");
	tester->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	tester->transform->Rotate(40, -40, 0);

	AddToScene(tester);

	// tests

	// GameObject* audio = CreateEmpty();
	// audio->AddComponent<AudioTester>();
	// audio->AddComponent<AudioSource>();
	// AddToScene(audio);

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
