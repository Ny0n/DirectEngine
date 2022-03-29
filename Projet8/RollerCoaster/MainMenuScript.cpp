#include "MainMenuScript.h"


MainMenuScript::MainMenuScript(Button* listBtn[3])
{
	_listBtn[0] = listBtn[0];
	_listBtn[1] = listBtn[1];
	_listBtn[2] = listBtn[2];
}

MainMenuScript::~MainMenuScript()
{
	//delete _image;
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

void MainMenuScript::OnCredits()
{
	Utils::Println("credits");
}

void MainMenuScript::OnQuit()
{
	Application::Quit();
}

// **************************** //

void MainMenuScript::Start()
{
	//_button->onClick = RUNNER(MyFunc);
	_listBtn[0]->onClick = RUNNER(OnPlay);
	_listBtn[1]->onClick = RUNNER(OnCredits);
	_listBtn[2]->onClick = RUNNER(OnQuit);
}

void MainMenuScript::Update()
{
	
}

