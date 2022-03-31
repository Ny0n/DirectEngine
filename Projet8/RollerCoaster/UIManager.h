#pragma once

#include "EngineLib.h"
#include "FPCam.h"

class UIManager : public MonoBehaviour
{
	string GetType() override { return NAMEOF(UIManager); }

	void Start() override;
	void Update() override;

public:
	explicit UIManager(GameObject* pauseGO, GameObject* crossGO, FPCam* cam, Textbox* fpsCounter, Textbox* timerText, Textbox* scoreText, Button* btnList[4]);
	~UIManager() override;

private:
	void Pause();
	void Resume();
	void Restart();
	void ShowFPS();
	void ShowTimer();
	void UpdateScore();

	GameObject* _pauseGO;
	GameObject* _crossGO;
	FPCam* _cam;

	Button* _listBtn[4];

	Textbox* _fpsCounter;
	Textbox* _timerText;
	Textbox* _scoreText;
	
	list<int> averageFPS;
};
