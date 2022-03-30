#pragma once

#include "EngineLib.h"
#include "FPCam.h"

class UIManager : public MonoBehaviour
{
	string GetType() override { return NAMEOF(UIManager); }

	void Start() override;
	void Update() override;

public:
	explicit UIManager(GameObject* goToEnable, GameObject* goToDisable, FPCam* cam, Button* listBtn[4], Textbox* fpsCounter);
	~UIManager() override;

	bool IsPaused();

private:
	void Pause();
	void Resume();
	void OnRestart();
	void OnMenu();
	void ShowFPS();

	bool isPaused;
	GameObject* _pauseGO;
	GameObject* _crossGO;
	FPCam* _cam;
	Button* _listBtn[4];
	Textbox* _fpsCounter;

	list<int> averageFPS;
};
