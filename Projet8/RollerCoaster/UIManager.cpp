#include "UIManager.h"

#include "App.h"
#include "GameManager.h"
#include "Options.h"

UIManager::UIManager(GameObject* pauseGO, GameObject* crossGO, FPCam* cam, Textbox* fpsCounter, Textbox* timerText, Textbox* scoreText, Button* btnList[4])
	: _pauseGO(pauseGO), _crossGO(crossGO), _cam(cam), _fpsCounter(fpsCounter), _timerText(timerText), _scoreText(scoreText)
{
	for (int i = 0; i < 4; i++)
	{
		_listBtn[i] = btnList[i];
	}
}

UIManager::~UIManager()
{
}

void UIManager::Pause()
{
	Cursor::SetVisible(true);

	_pauseGO->SetEnabled(true);
	_crossGO->SetEnabled(false);
	_cam->SetEnabled(false);
}

void UIManager::Resume()
{
	Cursor::SetVisible(false);

	_pauseGO->SetEnabled(false);
	_crossGO->SetEnabled(true);
	_cam->SetEnabled(true);
}

void UIManager::Restart()
{
	Cursor::SetVisible(false);
}

void UIManager::ShowFPS()
{
	auto currFps = static_cast<int>(Time::currentFps());

	if (averageFPS.size() >= 50)
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

void UIManager::ShowTimer()
{
	auto currTimer = GameManager::GetTimer();

	wstring strTimer = to_wstring(currTimer);

	_timerText->text = strTimer.substr(0, strTimer.find('.') + 3);

	if (currTimer <= Options::timerValue / 5)
		_timerText->textColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	else
		_timerText->textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void UIManager::UpdateScore()
{
	auto currScore = GameManager::GetScore();
	auto targetScore = Options::scoreMin;

	_scoreText->text = L"Score: " + to_wstring(currScore) + L"/" + to_wstring(targetScore);

	if (currScore >= targetScore)
		_scoreText->textColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	else
		_scoreText->textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

// **************************** //

// Start is called before the first frame update
void UIManager::Start()
{
	_listBtn[0]->onClick = RUNNER(Resume);
	_listBtn[1]->onClick = RUNNER(Restart);
}

// Update is called once per frame
void UIManager::Update()
{
	auto isPaused = GameManager::IsPaused();


	if (Options::showScore)
		UpdateScore();
	else
		_scoreText->SetEnabled(false);

	if (Options::showTimer && !isPaused)
		ShowTimer();
	else if (!isPaused)
		_timerText->SetEnabled(false);

	if (Options::showFps)
		ShowFPS();
	else
		_fpsCounter->SetEnabled(false);

	if (Engine::GetInstance()->window != GetForegroundWindow())
		Pause();

	if (isPaused)
		Pause();
	else
		Resume();
}

