#include "GameManager.h"

#include "Options.h"
#include "UIManager.h"

int GameManager::_score = 0;
float GameManager::_timer = 0;
bool GameManager::_isPaused = false;

GameManager::GameManager(Button* listBtn[4])
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

void GameManager::AddScore(int n)
{
	_score += n;
}

void GameManager::Pause()
{
	_isPaused = true;

	Cursor::Unlock();
}

void GameManager::Menu()
{
	_isPaused = false;
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
	Utils::Println("YOU WIN!!");
}

void GameManager::Lose()
{
	Utils::Println("YOU LOSE!!");
}

void GameManager::Draw()
{
	Utils::Println("YOU FINISHED THE GAME!!");
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

	//TODO CHECK IF GAME IS FINISHED

	if (Input::GetKeyDown(KeyCode::Tab) || Input::GetKeyDown(KeyCode::Escape))
	{
		if (_isPaused)
			_isPaused = false;
		else
			_isPaused = true;
	}

	if (_isPaused)
		Pause();
	else
		Resume();
}
