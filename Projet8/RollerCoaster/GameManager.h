#pragma once

#include "EngineLib.h"

class GameManager : public MonoBehaviour
{
	string GetType() override { return NAMEOF(GameManager); }

	void Start() override;
	void Update() override;

public:
	GameManager(Button* listBtn[4], Button* endBtn);
	~GameManager() override;
	static float GetTimer();
	static int GetScore();
	static bool IsPaused();
	static int GetGameStatus();

	static void AddScore(int n);

private:
	void EndGame();
	void Restart();
	void Resume();
	void Pause();
	void Menu();
	void Timer();
	void Win();
	void Lose();
	void Draw();

	static float _timer;
	static int _score;
	static bool _isPaused;

	static bool _won;
	static bool _lost;
	static bool _drew;

	Button* _listBtn[4];
	Button* _endBtn;
};
