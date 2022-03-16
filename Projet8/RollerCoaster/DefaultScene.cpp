#include "DefaultScene.h"

#include "Cube.h"
#include "GoUpAndRoll.h"
#include "RainbowBackground.h"

DefaultScene::DefaultScene()
{
	// rgb background

	GameObject* rgb = CreateEmpty();
	rgb->AddComponent(new RainbowBackground());
	Instantiate(rgb);

	// camera

	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	mainCamera->transform->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, -30.0f));
	Instantiate(mainCamera);

	// cube

	GameObject* cube = CreateEmpty();
	cube->AddComponent(new Cube());
	
	cube->transform->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	cube->transform->SetScale(cube->transform->GetScale()*1);
	cube->transform->RotatePitch(25);
	
	Instantiate(cube);

	// tigre

	GameObject* tigre = CreateEmpty();

	LPCWSTR path = L"Mesh\\tiger.x";
	tigre->AddComponent(new MeshRenderer(path));
	tigre->AddComponent(new GoUpAndRoll());

	tigre->transform->SetPosition(D3DXVECTOR3(2.0f, 1.0f, 0.0f));
	tigre->transform->RotatePitch(25);
	tigre->transform->SetScale(tigre->transform->GetScale() * 2);

	Instantiate(tigre);
}

DefaultScene::~DefaultScene()
{
	Utils::DeleteList(&gameObjects);
}
