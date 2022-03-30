#include "MenuScene.h"

#include "AudioTester.h"
#include "DontDestroyOnLoad.h"
#include "MainMenuScript.h"
#include "InputTester.h"

class InputField;

string MenuScene::GetName()
{
	return "MenuScene";
}

void MenuScene::GenerateContent()
{
#pragma region BackGround
	auto backgroundCanvas = CreateEmpty();

	auto BackgroundImg = backgroundCanvas->AddComponent<Image>();
	BackgroundImg->filePath = L"Image\\background.jpg";
	BackgroundImg->width = 1920;
	BackgroundImg->height = 1080;

	AddToScene(backgroundCanvas);
#pragma endregion BackGround

#pragma region Main Menu Canvas
	Button* menuBtnList[4] = {nullptr};

	GameObject* menuCanvas = CreateEmpty();

	auto PlayBtn = menuCanvas->AddComponent<Button>();
	PlayBtn->position = D3DXVECTOR2(1300, 500);
	PlayBtn->text = L"PLAY";
	menuBtnList[0] = PlayBtn;

	auto OptionBtn = menuCanvas->AddComponent<Button>();
	OptionBtn->position = D3DXVECTOR2(1300, menuBtnList[0]->position.y + 110);
	OptionBtn->text = L"OPTIONS";
	menuBtnList[1] = OptionBtn;

	auto CreditsBtn = menuCanvas->AddComponent<Button>();
	CreditsBtn->position = D3DXVECTOR2(1300, menuBtnList[1]->position.y + 110);
	CreditsBtn->text = L"CREDITS";
	menuBtnList[2] = CreditsBtn;

	auto QuitBtn = menuCanvas->AddComponent<Button>();
	QuitBtn->position = D3DXVECTOR2(1300, menuBtnList[2]->position.y + 110);
	QuitBtn->text = L"QUIT";
	menuBtnList[3] = QuitBtn;

	menuCanvas->AddComponent<Textbox>();

	AddToScene(menuCanvas);
#pragma endregion Main Menu Canvas

#pragma region Options Canvas
	auto optionsCanvas = CreateEmpty();

	auto optionsPanel = optionsCanvas->AddComponent<Image>();
	optionsPanel->filePath = L"Image\\blanc.png";
	optionsPanel->width = 1500;
	optionsPanel->height = 850;
	auto optionsPanelPosition = D3DXVECTOR2((SCREEN_WIDTH - optionsPanel->width) * .5f, (SCREEN_HEIGHT - optionsPanel->height) * .5f);
	optionsPanel->position = optionsPanelPosition;
	optionsPanel->imageColor = D3DCOLOR_ARGB(120, 153, 153, 153);

	auto optionsText = optionsCanvas->AddComponent<Textbox>();
	optionsText->text = L"OPTIONS";
	optionsText->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	optionsText->size = D3DXVECTOR2(380, 100);
	optionsText->fontHeight = 85;
	optionsText->position = optionsPanelPosition;

	auto optionsBtn = optionsCanvas->AddComponent<Button>();
	optionsBtn->text = L"BACK TO MENU";
	int padding = 30;
	optionsBtn->position.x = optionsPanelPosition.x + optionsPanel->width - optionsBtn->size.x - padding;
	optionsBtn->position.y = optionsPanelPosition.y + optionsPanel->height - optionsBtn->size.y - padding;

	AddToScene(optionsCanvas);
#pragma endregion Options Canvas

#pragma region Credits Canvas
	auto creditsCanvas = CreateEmpty();

	auto creditsPanel = creditsCanvas->AddComponent<Image>();
	creditsPanel->filePath = L"Image\\blanc.png";
	creditsPanel->width = 1500;
	creditsPanel->height = 850;
	auto creditsPanelPosition = D3DXVECTOR2((SCREEN_WIDTH - creditsPanel->width) * .5f, (SCREEN_HEIGHT - creditsPanel->height) * .5f);
	creditsPanel->position = creditsPanelPosition;
	creditsPanel->imageColor = D3DCOLOR_ARGB(120, 153, 153, 153);

	auto creditsText = creditsCanvas->AddComponent<Textbox>();
	creditsText->text = L"CREDITS";
	creditsText->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	creditsText->size = D3DXVECTOR2(380, 100);
	creditsText->fontHeight = 85;
	creditsText->position = creditsPanelPosition;

	auto creditsBtn = creditsCanvas->AddComponent<Button>();
	creditsBtn->text = L"BACK TO MENU";
	creditsBtn->position.x = creditsPanelPosition.x + creditsPanel->width - creditsBtn->size.x - padding;
	creditsBtn->position.y = creditsPanelPosition.y + creditsPanel->height - creditsBtn->size.y - padding;

	AddToScene(creditsCanvas);
#pragma endregion Credits Canvas

	auto MenuManager = CreateEmpty();
	const auto script = new MainMenuScript(menuCanvas, optionsCanvas, creditsCanvas, menuBtnList);
	MenuManager->AddComponent(script);
	AddToScene(MenuManager);

	GameObject* audio = CreateEmpty();
	audio->AddComponent<DontDestroyOnLoad>();
	audio->AddComponent<AudioTester>();
	audio->AddComponent<AudioSource>(L"Audio\\giveitup.wav", true, 0.6f);
	AddToScene(audio);
}
