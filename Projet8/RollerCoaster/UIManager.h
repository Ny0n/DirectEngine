#pragma once

#include "EngineLib.h"
#include "FPCam.h"

class UIManager : public MonoBehaviour
{
	string GetType() override { return NAMEOF(UIManager); }

	void Start() override;
	void Update() override;

public:
	explicit UIManager(GameObject* goToEnable, GameObject* goToDisable, FPCam* cam, Button* listBtn[3], Textbox* fpsCounter);
	~UIManager() override;

	bool IsPaused();

private:
	void Pause();
	void Resume();
	void OnRestart();
	void onMenu();

	bool isPaused;
	GameObject* _pauseGO;
	GameObject* _crossGO;
	FPCam* _cam;
	Button* _listBtn[3];
	Textbox* _fpsCounter;
};
