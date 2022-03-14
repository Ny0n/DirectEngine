#include "DefaultScene.h"

#include "RainbowBackground.h"

DefaultScene::DefaultScene()
{
	GameObject* rgb = CreateEmpty();
	rgb->AddComponent(new RainbowBackground());
	Instantiate(rgb);

	/*GameObject* camera = CreateEmpty();
	camera->AddComponent(new Camera());
	GameObject* obj1 = CreateEmpty();
	obj1->AddComponent(new MovableCube());

	GameObject* cube = CreateEmpty();
	Vector3 cubePosition;
	cubePosition.x = 1.0f;
	cubePosition.y = 1.0f;
	cubePosition.z = 1.0f;
	cube->transform->position = cubePosition;

	QUATERNION cubeRotation;
	cubeRotation.x = 1.0f;
	cubeRotation.y = 1.0f;
	cubeRotation.z = 1.0f;
	cube->transform->quaternion = cubeRotation;

	Vector3 cubeScale;
	cubeScale.x = 1.0f;
	cubeScale.y = 1.0f;
	cubeScale.z = 1.0f;
	cube->transform->scale = cubeScale;

	cube->AddComponent(new Cube(cube,2.0f));

	GameObject* cube2 = CreateEmpty();
	Vector3 cubePosition2;
	cubePosition2.x = -5.0f;
	cubePosition2.y = 1.0f;
	cubePosition2.z = 1.0f;
	cube2->transform->position = cubePosition2;

	QUATERNION cubeRotation2;
	cubeRotation2.x = 1.0f;
	cubeRotation2.y = 1.0f;
	cubeRotation2.z = 1.0f;
	cube2->transform->quaternion = cubeRotation2;

	Vector3 cubeScale2;
	cubeScale2.x = 1.0f;
	cubeScale2.y = 1.0f;
	cubeScale2.z = 1.0f;
	cube2->transform->scale = cubeScale2;

	cube2->AddComponent(new Cube(cube2, 2.0f));*/
}
