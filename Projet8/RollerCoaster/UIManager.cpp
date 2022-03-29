#include "UIManager.h"

UIManager::UIManager(GameObject* go, GameObject* goToDisable, FPCam* cam, Button* listBtn[3], Textbox* fpsCounter): _pauseGO(go), _crossGO(goToDisable), _cam(cam), _fpsCounter(fpsCounter)
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

void UIManager::OnMenu()
{
	SceneManager::LoadScene(1);
}

void UIManager::ShowFPS()
{
	auto currFps = static_cast<int>(Time::currentFps());

	if (averageFPS.size() >= 100)
	{
		averageFPS.pop_front();
		averageFPS.push_back(currFps);
	}
	else
		averageFPS.push_back(currFps);

	int fps = 0;

	for (auto e : averageFPS)
	{
		fps += e;
	}

	_fpsCounter->text = L"FPS: " + to_wstring(fps / averageFPS.size());
}

// **************************** //

// Start is called before the first frame update
void UIManager::Start()
{
	_listBtn[0]->onClick = RUNNER(Resume);
	_listBtn[1]->onClick = RUNNER(OnRestart);
	_listBtn[2]->onClick = RUNNER(OnMenu);

}

// Update is called once per frame
void UIManager::Update()
{
	ShowFPS();

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

