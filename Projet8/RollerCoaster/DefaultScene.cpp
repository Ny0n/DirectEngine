#include "DefaultScene.h"

#include "Cube.h"
#include "GoUp.h"
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
	Instantiate(mainCamera);

	// cube

	GameObject* cube1 = CreateEmpty();
	cube1->AddComponent(new Cube());
	cube1->AddComponent(new Collider);
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

	GameObject* tigre = CreateEmpty();

	LPCWSTR path = L"Mesh\\monkey.x";
	tigre->AddComponent(new MeshRenderer(path));
	tigre->AddComponent(new Move());
	tigre->AddComponent(new Collider);
	// tigre->AddComponent(new GoUp(8));
	tigre->AddComponent(new Rotate());

	tigre->transform->SetPosition(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	tigre->transform->RotateYaw(22);
	tigre->transform->SetScale(tigre->transform->GetScale() * 0.05f);
	Instantiate(tigre);

	GameObject* canvas = CreateEmpty();
	canvas->AddComponent(new Canvas());

	auto image = new Image();
	image->height = 80;
	image->width = 80;
	image->filePath = L"C:/Users/kperez/Documents/direct8/direct8/Projet8/RollerCoaster/Image.png";

	canvas->AddComponent(image);
	Instantiate(canvas);


}

DefaultScene::~DefaultScene()
{
	Utils::DeleteList(&gameObjects);
}
