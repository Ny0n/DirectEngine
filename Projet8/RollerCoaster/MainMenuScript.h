#pragma once

#include "EngineLib.h"

class MainMenuScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(MainMenuScript); }

	void Start() override;
	void Update() override;

public:
	explicit MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO, Button* listBtn[4], InputField* listInputField[4], CheckBox* listCheckBox[6], Textbox* timerIPText, Textbox* scoreIPText);
	~MainMenuScript() override;

private:
	void MyFunc();

	void OnPlay();
	void OnOptions();
	void OnCredits();
	void OnQuit();
	void BackToMenu();
	void ToggleAudio();
	void DisableTimer();
	void DisableScore();

	GameObject* _menuGO;
	GameObject* _optionsGO;
	GameObject* _creditsGO;

	Button* _listBtn[4];
	InputField* _listInputField[4];
	CheckBox* _listCheckBox[6];

	Textbox* _timerIPText;
	Textbox* _scoreIPText;
};

