#pragma once

#include "EngineLib.h"

class MainMenuScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(MainMenuScript); }

	void Start() override;
	void Update() override;

public:
	explicit MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO, Button* listBtn[4]);
	~MainMenuScript() override;

private:
	void MyFunc();

	void OnPlay();
	void OnOptions();
	void OnCredits();
	void OnQuit();
	void BackToMenu();

	GameObject* _menuGO;
	GameObject* _optionsGO;
	GameObject* _creditsGO;

	Button* _listBtn[4];
	float speed = 1.0f;
	bool noir = true;
};

