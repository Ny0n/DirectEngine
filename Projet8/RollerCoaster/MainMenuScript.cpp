#include "MainMenuScript.h"


MainMenuScript::MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO,Button* listBtn[4]) : _menuGO(menuGO), _optionsGO(optionsGO), _creditsGO(creditsGO)
{
	_listBtn[0] = listBtn[0];
	_listBtn[1] = listBtn[1];
	_listBtn[2] = listBtn[2];
	_listBtn[3] = listBtn[3];
}

MainMenuScript::~MainMenuScript()
{
	
}

void MainMenuScript::MyFunc()
{
	/*auto randX = rand() % 400;
	auto randY = rand() % 350;
	_button->rectTopLeft = D3DXVECTOR2(randX, randY);
	_button->rectBottomRight = D3DXVECTOR2(randX + 300, randY +50);*/
	
}

void MainMenuScript::OnPlay()
{
	SceneManager::LoadScene("DefaultScene");
	Cursor::SetVisible(false);
}

void MainMenuScript::OnOptions()
{
	_menuGO->SetEnabled(false);
	_optionsGO->SetEnabled(true);

	auto btn = _optionsGO->GetComponent<Button>();
	btn->onClick = RUNNER(BackToMenu);
}

void MainMenuScript::OnCredits()
{
	_menuGO->SetEnabled(false);
	_creditsGO->SetEnabled(true);

	auto btn = _creditsGO->GetComponent<Button>();
	btn->onClick = RUNNER(BackToMenu);
}

void MainMenuScript::OnQuit()
{
	Application::Quit();
}

void MainMenuScript::BackToMenu()
{
	_menuGO->SetEnabled(true);
	_optionsGO->SetEnabled(false);
	_creditsGO->SetEnabled(false);
}

// **************************** //

void MainMenuScript::Start()
{
	//_button->onClick = RUNNER(MyFunc);
	_listBtn[0]->onClick = RUNNER(OnPlay);
	_listBtn[1]->onClick = RUNNER(OnOptions);
	_listBtn[2]->onClick = RUNNER(OnCredits);
	_listBtn[3]->onClick = RUNNER(OnQuit);

	_menuGO->SetEnabled(true);

	//if the gameobject is never set to true it wont be destroyed
	_optionsGO->SetEnabled(true);
	_optionsGO->SetEnabled(false);

	//if the gameobject is never set to true it wont be destroyed
	_creditsGO->SetEnabled(true);
	_creditsGO->SetEnabled(false);
}

void MainMenuScript::Update()
{
	
}

