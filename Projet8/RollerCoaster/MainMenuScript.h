#pragma once

#include "EngineLib.h"

class MainMenuScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(MainMenuScript); }

	void Start() override;
	void Update() override;

public:
	explicit MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO, Button* listBtn[4], InputField* listInputField[4], CheckBox* listCheckBox[6], Textbox* timerIPText, Textbox* scoreIPText, GameObject* easterEggGO);
	~MainMenuScript() override;

private:
	void OnPlay();
	void OnOptions();
	void OnCredits();
	void OnQuit();
	void BackToMenu();
	void ToggleEasterEgg();
	void StartEasterEgg();
	void StopEasterEgg();
	void ToggleAudio();
	void DisableTimer();
	void DisableScore();
	void OnEnable() override;

	GameObject* _menuGO;
	GameObject* _optionsGO;
	GameObject* _creditsGO;
	GameObject* _easterEggGO;

	Button* _listBtn[4];
	InputField* _listInputField[4];
	CheckBox* _listCheckBox[6];

	Textbox* _timerIPText;
	Textbox* _scoreIPText;

	bool _playingEasterEgg = false;
};

