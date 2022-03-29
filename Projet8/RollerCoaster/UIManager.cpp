#include "UIManager.h"

UIManager::UIManager(GameObject* go, GameObject* goToDisable, FPCam* cam, Button* listBtn[3]): _pauseGO(go), _crossGO(goToDisable), _cam(cam)
{
	_listBtn[0] = listBtn[0];
	_listBtn[1] = listBtn[1];
	_listBtn[2] = listBtn[2];
}

UIManager::~UIManager()
{
}

bool UIManager::IsPaused()
{
	return isPaused;
}

void UIManager::Pause()
{
	_pauseGO->SetEnabled(true);
	_crossGO->SetEnabled(false);
	Cursor::Unlock();
	_cam->SetEnabled(false);
	isPaused = true;
}

void UIManager::Resume()
{
	_pauseGO->SetEnabled(false);
	_crossGO->SetEnabled(true);
	Cursor::Lock();
	_cam->SetEnabled(true);
	isPaused = false;
}

void UIManager::OnRestart()
{
	SceneManager::LoadScene(SceneManager::GetActiveSceneName());
	Cursor::SetVisible(false);
}

void UIManager::onMenu()
{
	SceneManager::LoadScene(1);
}

// **************************** //

// Start is called before the first frame update
void UIManager::Start()
{
	_listBtn[0]->onClick = RUNNER(Resume);
	_listBtn[1]->onClick = RUNNER(OnRestart);
	_listBtn[2]->onClick = RUNNER(onMenu);
}

// Update is called once per frame
void UIManager::Update()
{
	if (Engine::GetInstance()->window != GetForegroundWindow())
		Pause();

	if (Input::GetKeyDown(KeyCode::Tab) || Input::GetKeyDown(KeyCode::Escape))
	{
		if (isPaused)
			isPaused = false;
		else
			isPaused = true;
	}

	if (isPaused)
		Pause();
	else
		Resume();
}

