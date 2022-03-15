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
	Instantiate(camera);

	GameObject* cube = CreateEmpty();
	cube->transform->Identity();
	Instantiate(cube);

	D3DXVECTOR3 cubePosition;
	cubePosition.x = 0.0f;
	cubePosition.y = 0.0f;
	cubePosition.z = 0.0f;
	cube->transform->position = cubePosition;

	cube->transform->scale *= 2;

	cube->transform->RotateYaw(45);
	
	cube->AddComponent(new Cube(cube,2.0f));

	GameObject* cube2 = CreateEmpty();
	cube2->transform->Identity();
	Instantiate(cube2);

	D3DXVECTOR3 cubePosition2;
	cubePosition2.x = -5.0f;
	cubePosition2.y = 1.0f;
	cubePosition2.z = 1.0f;
	cube2->transform->position = cubePosition2;


	cube2->transform->RotatePitch(45);

	cube2->AddComponent(new Cube(cube2, 2.0f));

}

DefaultScene::~DefaultScene()
{
	FreeMemory(this->gameObjects);
}

void DefaultScene::FreeMemory(list<GameObject*> listGo)
{
	for (const GameObject* element : listGo)
	{
		delete element;
	}

	listGo.clear();
}

