#include "MenuScene.h"

#include "CECIESTUNSCRIPT.h"
#include "InputTester.h"

class InputField;

string MenuScene::GetName()
{
	return "MenuScene";
}

void MenuScene::GenerateContent()
{
	// canvas
	//auto camera = CreateEmpty();
	//camera->AddComponent<Camera>();
	//camera->transform->SetPosition(D3DXVECTOR3(0,-100,0));
	//AddToScene(camera);

	GameObject* canvas = CreateEmpty();

	/*const auto image = new Image();
	image->width = 200;
	image->height = 200;
	image->filePath = L"Image\\blanc.png";
	canvas->AddComponent(image);
	
	const auto tb = new Textbox();
	tb->drawBox = true;
	tb->drawBorder = true;
	canvas->AddComponent(tb);
	

	const auto script = new CECIESTUNSCRIPT(image, tb);
	canvas->AddComponent(script);*/

	auto ip = canvas->AddComponent<InputField>();
	ip->drawBorder = true;
	ip->drawBox = true;

	auto button = canvas->AddComponent<Button>();

	const auto script = new CECIESTUNSCRIPT(button);
	canvas->AddComponent(script);

	AddToScene(canvas);
}
