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
	AddToScene(mainCamera);

	/*GameObject* inputTester = CreateEmpty();
	inputTester->AddComponent<InputTester>();
	AddToScene(inputTester);*/

	//cart
	GameObject* cart = CreateEmpty();

	LPCWSTR cartPath = L"Mesh\\minecart.x";
	//cart->AddComponent<MeshRenderer>(cartPath);
	cart->AddComponent<MeshRenderer>(cartPath);

	AddToScene(cart);

	cam->SetCart(cart);


	// crosshair
	auto crossGO = CreateEmpty();
	auto img = crossGO->AddComponent<Image>();

	img->filePath = L"Image\\flavien3.png";
	img->position = D3DXVECTOR2(SCREEN_WIDTH * .5f, SCREEN_HEIGHT * .5f);
	img->originalSize = true;
	//img->scale = D3DXVECTOR2(.1f, .1f);
	img->scale = D3DXVECTOR2(.5f, .5f);
	img->imageColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	img->drawFromCenter = true;

	crossGO->AddComponent<CrosshairScript>(img);

	AddToScene(crossGO);

#pragma region fpsCounter
	auto fpsCounter = CreateEmpty();
	auto fpsText = fpsCounter->AddComponent<Textbox>();
	fpsText->size = D3DXVECTOR2(50, 25);
	fpsText->drawBox = true;

	AddToScene(fpsCounter);

#pragma endregion fpsCounter

	#pragma region pause

	// menu pause
	auto pauseCanvas = CreateEmpty();
	pauseCanvas->AddComponent<PauseScript>();

	// panel
	auto panel = pauseCanvas->AddComponent<Image>();
	panel->filePath = L"Image\\blanc.png";
	panel->height = 500;
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
	Button* listBtn[3] = {nullptr};

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
	restartBtn->position.y = resumeBtn->position.y + 100;
	listBtn[1] = restartBtn;

	auto menuBtn = pauseCanvas->AddComponent<Button>();
	menuBtn->text = L"BACK TO MENU";
	menuBtn->size = D3DXVECTOR2(250, 60);
	menuBtn->position.x = panelPosition.x + (panel->width * 0.5f) - menuBtn->size.x * .5f;
	menuBtn->position.y = restartBtn->position.y + 100;
	listBtn[2] = menuBtn;

	AddToScene(pauseCanvas);

	#pragma endregion pause

	// UI Manager
	auto UIManagerGO = CreateEmpty();

	const auto managerScript = new UIManager(pauseCanvas, crossGO, cam, listBtn, fpsText);
	UIManagerGO->AddComponent(managerScript);

	AddToScene(UIManagerGO);
}
