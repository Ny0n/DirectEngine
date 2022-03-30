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
#include "Score.h"
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
	mainCamera->AddComponent(new Camera());
	auto cam = mainCamera->AddComponent<FPCam>();
	mainCamera->transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	mainCamera->AddComponent<RailMaker>();
	mainCamera->AddComponent<MoveAlongRails>();
	mainCamera->AddComponent<Shoot>();
	mainCamera->AddComponent<AlignedBox>();
	AddToScene(mainCamera);

	/*GameObject* inputTester = CreateEmpty();
	inputTester->AddComponent<InputTester>();
	AddToScene(inputTester);*/

#pragma region cart
	GameObject* cart = CreateEmpty();

	LPCWSTR cartPath = L"Mesh\\minecart.x";
	//cart->AddComponent<MeshRenderer>(cartPath);
	cart->AddComponent<MeshRenderer>(cartPath);

	AddToScene(cart);

	cam->SetCart(cart);
#pragma endregion cart

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
	auto scoreGO = CreateEmpty();

	auto scoreText = scoreGO->AddComponent<Textbox>();
	scoreText->textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	scoreText->text = L"Score: 0";
	scoreText->size = D3DXVECTOR2(300, 50);
	scoreText->fontHeight = 50;
	scoreText->position = D3DXVECTOR2(SCREEN_WIDTH * .5f - scoreText->size.x * .5f, 75);

	scoreGO->AddComponent<Score>(scoreText);

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

	// UI Manager
	auto UIManagerGO = CreateEmpty();

	const auto managerScript = new UIManager(pauseCanvas, crossGO, cam, listBtn, fpsText);
	UIManagerGO->AddComponent(managerScript);

	AddToScene(UIManagerGO);

	

}