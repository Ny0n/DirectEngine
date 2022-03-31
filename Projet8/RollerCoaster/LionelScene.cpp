#include "LionelScene.h"

#include "GoUp.h"
#include "InputTester.h"
#include "Move.h"
#include "Shoot.h"

string LionelScene::GetName()
{
	return "LionelScene";
}

void LionelScene::GenerateContent()
{
	//collider
	GameObject* aligneBox = CreateEmpty();
	aligneBox->AddComponent<AlignedBox>();
	AddToScene(aligneBox);


	// Camera
	GameObject* Camera = CreateEmpty();

	//Camera Data
	Camera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -10.0f));

	// Camera Component
	auto cam = Camera->AddComponent<class Camera>();
	cam->ChangeSkyColor(D3DCOLOR_XRGB(255, 0, 0));
	//Camera->AddComponent<RealFPCam>();
	Camera->AddComponent<InputTester>();
	Camera->AddComponent<Move>();
	Camera->AddComponent<Shoot>();

	AddToScene(Camera);

	// particule

	GameObject* particuleTest = CreateEmpty();


	particuleTest->AddComponent<ParticleSystem>();
	//particuleTest->AddComponent<MeshRenderer>(L"Mesh\\tiger.x");

	AddToScene(particuleTest);
	

}
