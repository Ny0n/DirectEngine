#include "MenuScene.h"

#include "CECIESTUNSCRIPT.h"
#include "InputTester.h"

string MenuScene::GetName()
{
	return "MenuScene";
}

void MenuScene::GenerateContent()
{
	// canvas

	GameObject* canvas = CreateEmpty();

	const auto image = new Image();
	image->width = 200;
	image->height = 200;
	image->filePath = L"Image\\blanc.png";
	canvas->AddComponent(image);
	
	const auto tb = new Textbox();
	tb->drawBox = true;
	tb->drawBorder = true;
	canvas->AddComponent(tb);
	

	// const auto script = new CECIESTUNSCRIPT(image, tb);
	// canvas->AddComponent(script);

	AddToScene(canvas);
}
