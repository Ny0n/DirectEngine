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
	Button* btnList[3] = {nullptr};

	GameObject* canvas = CreateEmpty();

	auto BackgroundImg = canvas->AddComponent<Image>();
	BackgroundImg->filePath = L"Image\\test.jpg";
	BackgroundImg->width = 1920;
	BackgroundImg->height = 1080;

	auto PlayBtn = canvas->AddComponent<Button>();
	PlayBtn->position = D3DXVECTOR2(1300, 500);
	PlayBtn->text = L"PLAY";
	btnList[0] = PlayBtn;

	auto CreditsBtn = canvas->AddComponent<Button>();
	CreditsBtn->position = D3DXVECTOR2(1300, 650);
	CreditsBtn->text = L"CREDITS";
	btnList[1] = CreditsBtn;

	auto QuitBtn = canvas->AddComponent<Button>();
	QuitBtn->position = D3DXVECTOR2(1300, 800);
	QuitBtn->text = L"QUIT";
	btnList[2] = QuitBtn;

	auto tb = canvas->AddComponent<Textbox>();

	auto input = canvas->AddComponent<InputField>();

	const auto script = new CECIESTUNSCRIPT(btnList);
	canvas->AddComponent(script);

	AddToScene(canvas);
}
