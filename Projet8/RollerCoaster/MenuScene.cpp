#include "MenuScene.h"

string MenuScene::GetName()
{
	return "MenuScene";
}

void MenuScene::GenerateContent()
{
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
