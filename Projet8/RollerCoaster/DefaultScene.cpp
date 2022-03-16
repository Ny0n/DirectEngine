#include "DefaultScene.h"

#include "Cube.h"
#include "RainbowBackground.h"

DefaultScene::DefaultScene()
{
	GameObject* rgb = CreateEmpty();
	rgb->AddComponent(new RainbowBackground());
	Instantiate(rgb);

	GameObject* camera = CreateEmpty();
	camera->AddComponent(new Camera());

	camera->transform->SetPosition(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
	Instantiate(camera);

	GameObject* cube = CreateEmpty();
	cube->transform->Identity();
	Instantiate(cube);

	D3DXVECTOR3 cubePosition;
	cubePosition.x = 0.0f;
	cubePosition.y = 0.0f;
	cubePosition.z = 0.0f;
	camera->transform->SetPosition(cubePosition);

	cube->transform->SetScale(cube->transform->GetScale()*2);
	static float index = 0; index += 80;
	cube->transform->RotateYaw(index);
	
	cube->AddComponent(new Cube());

	GameObject* tigre = CreateEmpty();
	tigre->transform->Identity();
	Instantiate(tigre);
	
	D3DXVECTOR3 cubePosition2;
	cubePosition2.x = -5.0f;
	cubePosition2.y = 1.0f;
	cubePosition2.z = -20.0f;
	camera->transform->SetPosition(cubePosition2);
	
	tigre->transform->RotatePitch(25);
	
	LPCWSTR path1 = L"C:\\Users\\fcalvet\\Desktop\\direct8\\Projet8\\RollerCoaster\\Mesh\\tiger.x";
	LPCWSTR path2 = L"D:\\GitHub\\direct8\\Projet8\\RollerCoaster\\Mesh\\tiger.x";
	tigre->AddComponent(new MeshRenderer(path2));
}

DefaultScene::~DefaultScene()
{
	Utils::DeleteList(&gameObjects);
}
