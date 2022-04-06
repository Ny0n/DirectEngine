#include "UIManager.h"

#include "App.h"
#include "GameManager.h"
#include "Options.h"

UIManager::UIManager(GameObject* pauseGO, GameObject* crossGO, FPCam* cam, Textbox* fpsCounter, Textbox* timerText, Textbox* scoreText, GameObject* endgameGO, Textbox* endgameTitle, Textbox* endgameDesc, Textbox* endgameScore)
	: _pauseGO(pauseGO), _crossGO(crossGO), _cam(cam), _fpsCounter(fpsCounter), _timerText(timerText), _scoreText(scoreText), _endgameGO(endgameGO), _endgameTitle(endgameTitle), _endgameDesc(endgameDesc), _endgameScore(endgameScore)
{
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

	if (_averageFPS.size() >= 50)
	{
		_averageFPS.pop_front();
		_averageFPS.push_back(currFps);
	}
	else
		_averageFPS.push_back(currFps);

	int fps = 0;

	for (auto e : _averageFPS)
	{
		fps += e;
	}

	_fpsCounter->text = L"FPS: " + to_wstring(fps / _averageFPS.size());
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

void UIManager::EndGame()
{
	_endgameGO->SetEnabled(true);

	Cursor::SetVisible(true);

	_pauseGO->SetEnabled(false);
	_crossGO->SetEnabled(false);
	_cam->SetEnabled(false);
	_scoreText->SetEnabled(false);
	_timerText->SetEnabled(false);

	_endgameScore->text = L"Score: " + to_wstring(GameManager::GetScore()) + L'/' + to_wstring(Options::scoreMin);
}

void UIManager::Won()
{
	EndGame();

	_endgameTitle->text = L"You Won!";
	_endgameTitle->textColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	_endgameDesc->text = L"Congratulations " + Options::pseudo + L"!";
}

void UIManager::Lost()
{
	EndGame();

	_endgameTitle->text = L"You Lost!";
	_endgameTitle->textColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	_endgameDesc->text = L"Better luck next time " + Options::pseudo + L"!";
}

void UIManager::Drew()
{
	EndGame();

	_endgameTitle->text = L"Finished!";

	_endgameDesc->text = L"Hope you liked playing " + Options::pseudo + L"!";
}

// **************************** //

// Start is called before the first frame update
void UIManager::Start()
{	
	//An object whose never been enabled isnt destroyed
	_endgameGO->SetEnabled(true);
	_endgameGO->SetEnabled(false);
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
	
	if (isPaused)
		Pause();
	else
		Resume();

	int status = GameManager::GetGameStatus();
	if (status != 0)
	{
		switch (status)
		{
		case 1:
			Won();
			break;
		case 2:
			Lost();
			break;
		case 3:
			Drew();
			break;
		default:
			Utils::PrintErr("Unexpected game status value.");
			break;
		}
	}
}

