#include "UIManager.h"


UIManager::UIManager(Button* listBtn[3])
{
	_listBtn[0] = listBtn[0];
	_listBtn[1] = listBtn[1];
	_listBtn[2] = listBtn[2];
}

UIManager::~UIManager()
{
	//delete _image;
}

void UIManager::MyFunc()
{
	/*auto randX = rand() % 400;
	auto randY = rand() % 350;
	_button->rectTopLeft = D3DXVECTOR2(randX, randY);
	_button->rectBottomRight = D3DXVECTOR2(randX + 300, randY +50);*/
	
}

void UIManager::OnPlay()
{
	SceneManager::LoadScene("DefaultScene");
	Cursor::SetVisible(false);
}

void UIManager::OnCredits()
{
	Utils::Println("credits");
}

void UIManager::OnQuit()
{
	Application::Quit();
}

// **************************** //

void UIManager::Start()
{
	//_button->onClick = RUNNER(MyFunc);
	_listBtn[0]->onClick = RUNNER(OnPlay);
	_listBtn[1]->onClick = RUNNER(OnCredits);
	_listBtn[2]->onClick = RUNNER(OnQuit);
}

void UIManager::Update()
{
	
}

