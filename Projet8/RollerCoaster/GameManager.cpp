#include "GameManager.h"

#include "Options.h"
#include "UIManager.h"

int GameManager::_score = 0;
float GameManager::_timer = 0;
bool GameManager::_isPaused = false;
bool GameManager::_won = false;
bool GameManager::_lost = false;
bool GameManager::_drew = false;

GameManager::GameManager(Button* listBtn[4], Button* endBtn) : _endBtn(endBtn)
{
	for (int i = 0; i < 4; i++)
	{
		_listBtn[i] = listBtn[i];
	}
}

GameManager::~GameManager()
{
}

float GameManager::GetTimer()
{
	return _timer;
}

int GameManager::GetScore()
{
	return _score;
}

bool GameManager::IsPaused()
{
	return _isPaused;
}

int GameManager::GetGameStatus()
{
	if (_won)
		return 1;
	else if (_lost)
		return 2;
	else if (_drew)
		return 3;
	else
		return 0;
}

void GameManager::AddScore(int n)
{
	_score += n;
}

void GameManager::EndGame()
{
	_isPaused = false;
	SceneManager::LoadScene(1);

	_score = 0;
	_timer = Options::timerValue;
	_won = false;
	_lost = false;
	_drew = false;
}

void GameManager::Pause()
{
	_isPaused = true;

	Cursor::Unlock();
}

void GameManager::Menu()
{
	_isPaused = false;

	_score = 0;
	_timer = Options::timerValue;

	SceneManager::LoadScene(1);
}

void GameManager::Resume()
{
	_isPaused = false;

	Cursor::Lock();
}

void GameManager::Restart()
{
	SceneManager::LoadScene(SceneManager::GetActiveSceneName());

	_score = 0;
	_timer = Options::timerValue;

	Resume();
}

void GameManager::Timer()
{
	_timer -= Time::deltaTime;
}

void GameManager::Win()
{
	_won = true;

	Pause();
}

void GameManager::Lose()
{
	_lost = true;
	
	Pause();
}

void GameManager::Draw()
{
	_drew = true;
	
	Pause();
}

// **************************** //

// Start is called before the first frame update
void GameManager::Start()
{
	_timer = Options::timerValue;

	_listBtn[0]->onClick = RUNNER(Resume);
	_listBtn[1]->onClick = RUNNER(Restart);
	_listBtn[2]->onClick = RUNNER(Menu);
	_listBtn[3]->onClick = Application::Quit;

	_endBtn->onClick = RUNNER(EndGame);
}

// Update is called once per frame
void GameManager::Update()
{
	if (Engine::GetInstance()->window != GetForegroundWindow())
		Pause();

	if (Options::showTimer)
	{
		Timer();

		if (_timer <= 0)
		{
			if (Options::showScore)
			{
				if (_score >= Options::scoreMin)
					Win();
				else
					Lose();
			}
			else
				Draw();
		}
	}
	else if (_score >= Options::scoreMin && Options::showScore)
			Win();

	if (GameManager::GetGameStatus() == 0)
	{
		if (Input::GetKeyDown(KeyCode::Tab) || Input::GetKeyDown(KeyCode::Escape))
		{
			if (_isPaused)
				_isPaused = false;
			else
				_isPaused = true;
		}
	}

	if (_isPaused)
		Pause();
	else
		Resume();
}
