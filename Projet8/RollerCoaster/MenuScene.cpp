#include "MenuScene.h"

#include "AudioTester.h"
#include "CheckBox.h"
#include "DontDestroyOnLoad.h"
#include "MainMenuScript.h"
#include "InputTester.h"
#include "SingletonTest.h"

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

	auto logoImg = menuCanvas->AddComponent<Image>();
	logoImg->filePath = L"Image\\mine.png";
	logoImg->position = D3DXVECTOR2(500, 50);
	logoImg->originalSize = true;

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

	AddToScene(menuCanvas);
#pragma endregion Main Menu Canvas

#pragma region Options Canvas
	auto optionsCanvas = CreateEmpty();

	InputField* inputOptionsList[3] = {nullptr};
	CheckBox* checkboxOptionsList[5] = {nullptr};

	int padding = 30;

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
	optionsBtn->position.x = optionsPanelPosition.x + optionsPanel->width - optionsBtn->size.x - padding;
	optionsBtn->position.y = optionsPanelPosition.y + optionsPanel->height - optionsBtn->size.y - padding;

	auto playerCategory = optionsCanvas->AddComponent<Textbox>();
	playerCategory->text = L"Player Informations";
	playerCategory->fontHeight = 42;
	playerCategory->size.x = 320;
	playerCategory->textFormat = DT_LEFT | DT_VCENTER;
	playerCategory->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	playerCategory->position.x = optionsPanelPosition.x + padding * 2;
	playerCategory->position.y = optionsPanelPosition.y + padding + 170;

	auto playerName = optionsCanvas->AddComponent<Textbox>();
	playerName->text = L"Name: ";
	playerName->position.x = playerCategory->position.x + padding * 2;
	playerName->position.y = playerCategory->position.y + padding * 3;
	playerName->textFormat = DT_LEFT | DT_VCENTER;
	playerName->size.x = 80;
	playerName->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);

	auto playerInputField = optionsCanvas->AddComponent<InputField>();
	playerInputField->position.x = playerName->position.x + playerName->size.x;
	playerInputField->position.y = playerName->position.y + 5;
	playerInputField->size.x = 200;
	playerInputField->size.y = 40;
	playerInputField->textMaxCaracters = 15;
	inputOptionsList[0] = playerInputField;

	auto playerSpeed = optionsCanvas->AddComponent<Textbox>();
	playerSpeed->text = L"Speed: ";
	playerSpeed->position.x = playerCategory->position.x + padding * 2;
	playerSpeed->position.y = playerName->position.y + 70;
	playerSpeed->textFormat = DT_LEFT | DT_VCENTER;
	playerSpeed->size.x = 80;
	playerSpeed->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);

	auto speedInputField = optionsCanvas->AddComponent<InputField>();
	speedInputField->position.x = playerSpeed->position.x + playerSpeed->size.x;
	speedInputField->position.y = playerSpeed->position.y + 5;
	speedInputField->size.x = 200;
	speedInputField->size.y = 40;
	speedInputField->textMaxCaracters = 3;
	inputOptionsList[1] = speedInputField;

	auto timerCategory = optionsCanvas->AddComponent<Textbox>();
	timerCategory->text = L"Timer Options";
	timerCategory->fontHeight = 42;
	timerCategory->size.x = 320;
	timerCategory->textFormat = DT_LEFT | DT_VCENTER;
	timerCategory->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	timerCategory->position.x = playerCategory->position.x + playerCategory->size.x + 350;
	timerCategory->position.y = optionsPanelPosition.y + padding + 170;

	auto showTimer = optionsCanvas->AddComponent<CheckBox>();
	showTimer->text = L"Show Timer";
	showTimer->fontHeight = 25;
	showTimer->position.x = timerCategory->position.x + padding * 2;
	showTimer->position.y = timerCategory->position.y + padding * 3;
	checkboxOptionsList[0] = showTimer;

	auto timerValue = optionsCanvas->AddComponent<Textbox>();
	timerValue->text = L"Value: ";
	timerValue->position.x = timerCategory->position.x + padding * 2;
	timerValue->position.y = showTimer->position.y + 70;
	timerValue->textFormat = DT_LEFT | DT_VCENTER;
	timerValue->size.x = 80;
	timerValue->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);

	auto valueInputField = optionsCanvas->AddComponent<InputField>();
	valueInputField->position.x = timerValue->position.x + timerValue->size.x;
	valueInputField->position.y = timerValue->position.y + 5;
	valueInputField->size.x = 200;
	valueInputField->size.y = 40;
	valueInputField->textMaxCaracters = 3;
	inputOptionsList[2] = valueInputField;

	auto fpsCategory = optionsCanvas->AddComponent<Textbox>();
	fpsCategory->text = L"General Options";
	fpsCategory->fontHeight = 42;
	fpsCategory->size.x = 320;
	fpsCategory->textFormat = DT_LEFT | DT_VCENTER;
	fpsCategory->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	fpsCategory->position.x = playerCategory->position.x;
	fpsCategory->position.y = playerCategory->position.y + 250;

	auto showFPS = optionsCanvas->AddComponent<CheckBox>();
	showFPS->text = L"Show FPS";
	showFPS->fontHeight = 25;
	showFPS->position.x = fpsCategory->position.x + padding * 2;
	showFPS->position.y = fpsCategory->position.y + padding * 3;
	checkboxOptionsList[1] = showFPS;

	auto toggleAudio = optionsCanvas->AddComponent<CheckBox>();
	toggleAudio->text = L"Toggle Audio";
	toggleAudio->fontHeight = 25;
	toggleAudio->position.x = fpsCategory->position.x + padding * 2;
	toggleAudio->position.y = showFPS->position.y + 50;
	checkboxOptionsList[2] = toggleAudio;

	auto crosshairCategory = optionsCanvas->AddComponent<Textbox>();
	crosshairCategory->text = L"Crosshair Options";
	crosshairCategory->fontHeight = 42;
	crosshairCategory->size.x = 320;
	crosshairCategory->textFormat = DT_LEFT | DT_VCENTER;
	crosshairCategory->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	crosshairCategory->position.x = timerCategory->position.x;
	crosshairCategory->position.y = timerCategory->position.y + 250;
	
	auto rotatingCrosshair = optionsCanvas->AddComponent<CheckBox>();
	rotatingCrosshair->text = L"Rotating Crosshair";
	rotatingCrosshair->fontHeight = 25;
	rotatingCrosshair->textBoxWidth = 200;
	rotatingCrosshair->position.x = crosshairCategory->position.x + padding * 2;
	rotatingCrosshair->position.y = crosshairCategory->position.y + padding * 3;
	checkboxOptionsList[3] = rotatingCrosshair;

	auto pulsingCrosshair = optionsCanvas->AddComponent<CheckBox>();
	pulsingCrosshair->text = L"Pulsing Crosshair";
	pulsingCrosshair->fontHeight = 25;
	pulsingCrosshair->textBoxWidth = 200;
	pulsingCrosshair->position.x = crosshairCategory->position.x + padding * 2;
	pulsingCrosshair->position.y = rotatingCrosshair->position.y + 50;
	checkboxOptionsList[4] = pulsingCrosshair;

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

	auto groupeText = creditsCanvas->AddComponent<Textbox>();
	groupeText->text = L"~~ Groupe 7 ~~";
	groupeText->fontHeight = 60;
	groupeText->size.x = 350;
	groupeText->textColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	groupeText->position.x = SCREEN_WIDTH * .5f - groupeText->size.x * .5f;
	groupeText->position.y = creditsPanelPosition.y + 200;

	auto flavienText = creditsCanvas->AddComponent<Textbox>();
	flavienText->text = L"Flavien MERITTO";
	flavienText->fontHeight = 40;
	flavienText->size.x = 300;
	flavienText->textColor = D3DCOLOR_ARGB(255, 10, 240, 163);
	flavienText->position.x = SCREEN_WIDTH * .5f - flavienText->size.x *.5f;
	flavienText->position.y = groupeText->position.y + flavienText->size.y + 60;

	auto lionelText = creditsCanvas->AddComponent<Textbox>();
	lionelText->text = L"Lionel JANIN";
	lionelText->fontHeight = 40;
	lionelText->size.x = 300;
	lionelText->textColor = D3DCOLOR_ARGB(255, 30, 30, 255);
	lionelText->position.x = SCREEN_WIDTH * .5f - lionelText->size.x * .5f;
	lionelText->position.y = flavienText->position.y + lionelText->size.y + 30;

	auto franText = creditsCanvas->AddComponent<Textbox>();
	franText->text = L"François CALVET";
	franText->fontHeight = 40;
	franText->size.x = 300;
	franText->textColor = D3DCOLOR_ARGB(255, 255,0,0);
	franText->position.x = SCREEN_WIDTH * .5f - franText->size.x * .5f;
	franText->position.y = lionelText->position.y + franText->size.y + 30;

	auto killianText = creditsCanvas->AddComponent<Textbox>();
	killianText->text = L"Killian PEREZ";
	killianText->fontHeight = 40;
	killianText->size.x = 300;
	killianText->textColor = D3DCOLOR_ARGB(255, 255, 255, 0);
	killianText->position.x = SCREEN_WIDTH * .5f - killianText->size.x * .5f;
	killianText->position.y = franText->position.y + killianText->size.y + 30;

	auto creditsBtn = creditsCanvas->AddComponent<Button>();
	creditsBtn->text = L"BACK TO MENU";
	creditsBtn->position.x = creditsPanelPosition.x + creditsPanel->width - creditsBtn->size.x - padding;
	creditsBtn->position.y = creditsPanelPosition.y + creditsPanel->height - creditsBtn->size.y - padding;

	AddToScene(creditsCanvas);
#pragma endregion Credits Canvas

	auto MenuManager = CreateEmpty();
	const auto script = new MainMenuScript(menuCanvas, optionsCanvas, creditsCanvas, menuBtnList, inputOptionsList, checkboxOptionsList);
	MenuManager->AddComponent(script);
	AddToScene(MenuManager);

	GameObject* audio = CreateEmpty();
	audio->AddComponent<AudioTester>();
	audio->AddComponent<AudioSource>(L"Audio\\giveitup.wav", true, 0.6f);
	AddToScene(audio);

	// GameObject* stest = CreateEmpty();
	// stest->AddComponent<SingletonTest>();
	// AddToScene(stest);
}
