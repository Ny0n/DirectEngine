﻿#pragma once

#include "EngineLib.h"
#include "FPCam.h"

class UIManager : public MonoBehaviour
{
	string GetType() override { return NAMEOF(UIManager); }

	void Start() override;
	void Update() override;

public:
	explicit UIManager(GameObject* pauseGO, GameObject* crossGO, FPCam* cam, Textbox* fpsCounter, Textbox* timerText, Textbox* scoreText, Button* btnList[4], GameObject* endgameGO, Textbox* endgameTitle, Textbox* endgameDesc, Textbox* endgameScore);
	~UIManager() override;

private:
	void Pause();
	void Resume();
	void Restart();
	void ShowFPS();
	void ShowTimer();
	void UpdateScore();

	void EndGame();
	void Won();
	void Lost();
	void Drew();

	GameObject* _endgameGO;
	GameObject* _pauseGO;
	GameObject* _crossGO;
	FPCam* _cam;

	Button* _listBtn[4];

	Textbox* _fpsCounter;
	Textbox* _timerText;
	Textbox* _scoreText;

	Textbox* _endgameTitle;
	Textbox* _endgameDesc;
	Textbox* _endgameScore;
	
	list<int> _averageFPS;
};
