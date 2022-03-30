#pragma once

#include "EngineLib.h"

class MainMenuScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(MainMenuScript); }

	void Start() override;
	void Update() override;

public:
	explicit MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO, Button* listBtn[4], InputField* listInputField[3], CheckBox* listCheckBox[5]);
	~MainMenuScript() override;

private:
	void MyFunc();

	void OnPlay();
	void OnOptions();
	void OnCredits();
	void OnQuit();
	void BackToMenu();
	void ToggleAudio();

	GameObject* _menuGO;
	GameObject* _optionsGO;
	GameObject* _creditsGO;

	Button* _listBtn[4];
	InputField* _listInputField[3];
	CheckBox* _listCheckBox[5];

	float speed = 1.0f;
	bool noir = true;
};

