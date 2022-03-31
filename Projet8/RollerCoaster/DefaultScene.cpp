#include "DefaultScene.h"

#include "CrosshairScript.h"
#include "Cube.h"
#include "DontDestroyOnLoad.h"
#include "GoUp.h"
#include "FPCam.h"
#include "InputTester.h"
#include "Move.h"
#include "MoveAlongRails.h"
#include "PauseScript.h"
#include "RailMaker.h"
#include "RainbowBackground.h"
#include "Rotate.h"
#include "GameManager.h"
#include "Shoot.h"
#include "UIManager.h"

string DefaultScene::GetName()
{
	return "DefaultScene";
}

void DefaultScene::GenerateContent()
{
	// tests
	GameObject* mainCamera = CreateEmpty();
	mainCamera->AddComponent<Camera>();
	auto fpCam = mainCamera->AddComponent<FPCam>();
	mainCamera->AddComponent<RailMaker>();
	mainCamera->AddComponent<MoveAlongRails>();
	mainCamera->AddComponent<Shoot>();
	mainCamera->AddComponent<AlignedBox>();
	auto light = mainCamera->AddComponent<PointLight>(D3DCOLOR_RGBA(255, 100, 0, 255), 100);
	light->offset = DATASUPPLIER( mainCamera->transform->GetUp() * -5 );
	AddToScene(mainCamera);

	// GameObject* inputTester = CreateEmpty();
	// inputTester->AddComponent<InputTester>();
	// AddToScene(inputTester);

#pragma region cart
	GameObject* cart = CreateEmpty();

	LPCWSTR cartPath = L"Mesh\\minecart.x";
	//cart->AddComponent<MeshRenderer>(cartPath);
	cart->AddComponent<MeshRenderer>(cartPath);

	AddToScene(cart);

	fpCam->SetCart(cart);
#pragma endregion cart

#pragma region particle
	GameObject* particle = CreateEmpty();
	
	particle->AddComponent<ParticleSystem>();

	AddToScene(particle);

	fpCam->SetParticle(particle);

#pragma endregion particle

#pragma region crosshair
	auto crossGO = CreateEmpty();
	auto img = crossGO->AddComponent<Image>();

	img->filePath = L"Image\\flavien3.png";
	img->position = D3DXVECTOR2(SCREEN_WIDTH * .5f, SCREEN_HEIGHT * .5f);
	img->originalSize = true;
	img->scale = D3DXVECTOR2(.5f, .5f);
	img->imageColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	img->drawFromCenter = true;

	crossGO->AddComponent<CrosshairScript>(img);

	AddToScene(crossGO);
#pragma endregion crosshair

#pragma region fpsCounter
	auto fpsCounter = CreateEmpty();
	auto fpsText = fpsCounter->AddComponent<Textbox>();
	fpsText->size = D3DXVECTOR2(90, 25);
	fpsText->textFormat = DT_LEFT | DT_VCENTER;
	fpsText->textColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	AddToScene(fpsCounter);

#pragma endregion fpsCounter

#pragma region Score
	int Ypadding = 75;

	//FPS Counter is not included in HUD
	int hudTextSize = 50;
	auto hudColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	auto scoreGO = CreateEmpty();

	auto scoreText = scoreGO->AddComponent<Textbox>();
	scoreText->textColor = hudColor;
	scoreText->text = L"Score: 0";
	scoreText->size = D3DXVECTOR2(300, 50);
	scoreText->fontHeight = hudTextSize;
	scoreText->position = D3DXVECTOR2(SCREEN_WIDTH * .5f - scoreText->size.x * .5f, Ypadding);
	
	AddToScene(scoreGO);
#pragma endregion Score

#pragma region pause
	// menu pause
	auto pauseCanvas = CreateEmpty();
	pauseCanvas->AddComponent<PauseScript>();

	// panel
	auto panel = pauseCanvas->AddComponent<Image>();
	panel->filePath = L"Image\\blanc.png";
	panel->height = 520;
	panel->width = 500;
	auto panelPosition = D3DXVECTOR2((SCREEN_WIDTH - panel->width) * .5f, (SCREEN_HEIGHT - panel->height) * .5f);
	panel->position = panelPosition;
	panel->imageColor = D3DCOLOR_ARGB(120, 153, 153, 153);

	// title
	auto pauseTitle = pauseCanvas->AddComponent<Textbox>();
	pauseTitle->text = L"PAUSE";
	pauseTitle->textColor = D3DCOLOR_ARGB(120, 255, 255, 255);
	pauseTitle->fontHeight = 100;
	pauseTitle->fontWeight = FW_BOLD;
	pauseTitle->size = D3DXVECTOR2(300, 100);
	pauseTitle->position = D3DXVECTOR2(panelPosition.x + (panel->width * 0.5f) - pauseTitle->size.x *.5f, panelPosition.y + 30);

	//Buttons
	Button* listBtn[4] = {nullptr};

	auto resumeBtn = pauseCanvas->AddComponent<Button>();
	resumeBtn->text = L"RESUME";
	resumeBtn->size = D3DXVECTOR2(250 , 60);
	resumeBtn->position.x = panelPosition.x + (panel->width * 0.5f) - resumeBtn->size.x * .5f;
	resumeBtn->position.y = panelPosition.y + 175;
	listBtn[0] = resumeBtn;

	auto restartBtn = pauseCanvas->AddComponent<Button>();
	restartBtn->text = L"RESTART";
	restartBtn->size = D3DXVECTOR2(250, 60);
	restartBtn->position.x = panelPosition.x + (panel->width * 0.5f) - restartBtn->size.x * .5f;
	restartBtn->position.y = resumeBtn->position.y + 80;
	listBtn[1] = restartBtn;

	auto menuBtn = pauseCanvas->AddComponent<Button>();
	menuBtn->text = L"BACK TO MENU";
	menuBtn->size = D3DXVECTOR2(250, 60);
	menuBtn->position.x = panelPosition.x + (panel->width * 0.5f) - menuBtn->size.x * .5f;
	menuBtn->position.y = restartBtn->position.y + 80;
	listBtn[2] = menuBtn;

	auto quitBtn = pauseCanvas->AddComponent<Button>();
	quitBtn->text = L"QUIT";
	quitBtn->size = D3DXVECTOR2(250, 60);
	quitBtn->position.x = panelPosition.x + (panel->width * 0.5f) - quitBtn->size.x * .5f;
	quitBtn->position.y = menuBtn->position.y + 80;
	listBtn[3] = quitBtn;

	AddToScene(pauseCanvas);
#pragma endregion pause

#pragma region Timer
	auto timerGO = CreateEmpty();

	auto timerText = timerGO->AddComponent<Textbox>();
	timerText->text = L"000.00";
	timerText->fontHeight = hudTextSize;
	timerText->textColor = hudColor;
	timerText->position.x = SCREEN_WIDTH * .5f - timerText->size.x * .5f;
	timerText->position.y = SCREEN_HEIGHT - timerText->size.y - Ypadding;

	AddToScene(timerGO);
#pragma endregion Timer

#pragma region EndGame
	auto endgameGO = CreateEmpty();

	int yPadding = 30;

	auto endgamePanel = endgameGO->AddComponent<Image>();
	D3DXVECTOR2 endgamePanelPos;
	endgamePanel->filePath = L"Image\\blanc.png";
	endgamePanel->imageColor = D3DCOLOR_ARGB(120, 153, 153, 153);
	endgamePanel->width = 900;
	endgamePanel->height = 450;
	endgamePanelPos.x = SCREEN_WIDTH * .5f - endgamePanel->width * .5f;
	endgamePanelPos.y = 300;
	endgamePanel->position = endgamePanelPos;

	auto endgameTitle = endgameGO->AddComponent<Textbox>();
	endgameTitle->text = L"FINISHED!";
	endgameTitle->size.x += 50;
	endgameTitle->position.x = endgamePanelPos.x + (endgamePanel->width * 0.5f) - endgameTitle->size.x * .5f;
	endgameTitle->position.y = endgamePanel->position.y + yPadding;
	endgameTitle->fontWeight = FW_BOLD;
	endgameTitle->fontHeight = 60;
	endgameTitle->textColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	auto endgameDesc = endgameGO->AddComponent<Textbox>();
	endgameDesc->text = L"Better luck next time Default User!";
	endgameDesc->fontHeight = 30;
	endgameDesc->size.x += 200;
	endgameDesc->position.x = endgamePanelPos.x + (endgamePanel->width * 0.5f) - endgameDesc->size.x * .5f;
	endgameDesc->position.y = endgameTitle->position.y + endgameTitle->size.y + 20;
	endgameDesc->textColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	auto endgameScore = endgameGO->AddComponent<Textbox>();
	endgameScore->text = L"Score: 0000";
	endgameScore->fontHeight = 40;
	endgameScore->position.x = endgamePanelPos.x + (endgamePanel->width * 0.5f) - endgameScore->size.x * .5f;
	endgameScore->position.y = endgameDesc->position.y + endgameDesc->size.y + 50;
	endgameScore->textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	
	auto endBtn = endgameGO->AddComponent<Button>();
	endBtn->text = L"BACK TO MENU";
	endBtn->size = D3DXVECTOR2(250, 60);
	endBtn->position.x = endgamePanelPos.x + (endgamePanel->width * 0.5f) - endBtn->size.x * .5f;
	endBtn->position.y = endgamePanelPos.y + endgamePanel->height - endBtn->size.y - yPadding;

	endgameGO->SetEnabled(false);

	AddToScene(endgameGO);
#pragma endregion EndGame

#pragma region UIManager
	auto UIManagerGO = CreateEmpty();

	const auto managerScript = new UIManager(pauseCanvas, crossGO, fpCam, fpsText, timerText, scoreText, listBtn, endgameGO);
	UIManagerGO->AddComponent(managerScript);

	AddToScene(UIManagerGO);
#pragma endregion UIManager

#pragma region GameManager
	auto gameManagerGO = CreateEmpty();

	const auto gameManagerScript = new GameManager(listBtn);
	gameManagerGO->AddComponent(gameManagerScript);

	AddToScene(gameManagerGO);
#pragma endregion GameManager

}