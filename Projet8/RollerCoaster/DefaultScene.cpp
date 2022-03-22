#include "DefaultScene.h"

#include "Cube.h"
#include "GoUp.h"
#include "RailMaker.h"
#include "InputTester.h"
#include "Move.h"
#include "RainbowBackground.h"
#include "Rotate.h"

DefaultScene::DefaultScene()
{
	// tests

	GameObject* inputTester = CreateEmpty();
	inputTester->AddComponent(new InputTester());
	Instantiate(inputTester);

	// rgb background

	GameObject* rgb = CreateEmpty();
	rgb->AddComponent(new RainbowBackground());
	Instantiate(rgb);

	GameObject* aligneBox = CreateEmpty();
	aligneBox->AddComponent(new AlignedBox());
	Instantiate(aligneBox);
	// camera

	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent(new Camera());
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent(new RailMaker(this));
	mainCamera->AddComponent(new Move());
	Instantiate(mainCamera);

	// cube

	GameObject* cube1 = CreateEmpty();
	cube1->AddComponent(new Cube());
	cube1->AddComponent(new Collider());
	
	cube1->AddComponent(new Rotate(150.0f, true));
	
	cube1->transform->SetPosition(D3DXVECTOR3(0.0f , 0.0f, 0.0f));
	cube1->transform->Rotate(40, -40, 0);
	
	Instantiate(cube1);

	GameObject* cube2 = CreateEmpty();
	cube2->AddComponent(new Cube());
	cube2->AddComponent(new Collider);
	cube2->AddComponent(new Rotate(150.0f));
	
	cube2->transform->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	cube2->transform->Rotate(40, 40, 0);
	
	Instantiate(cube2);

	// tigre

	//GameObject* tigre = CreateEmpty();

	//LPCWSTR path = L"Mesh\\monkey.x";
	//tigre->AddComponent(new MeshRenderer(path));
	//tigre->AddComponent(new Move());
	//tigre->AddComponent(new Collider);
	//// tigre->AddComponent(new GoUp(8));
	//tigre->AddComponent(new Rotate());

	//tigre->transform->SetPosition(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	//tigre->transform->RotateYaw(22);
	//tigre->transform->SetScale(tigre->transform->GetScale() * 0.05f);

	//Instantiate(tigre);
}

DefaultScene::~DefaultScene()
{
	Utils::DeleteList(&gameObjects);
}
