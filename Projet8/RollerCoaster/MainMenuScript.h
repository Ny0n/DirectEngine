#pragma once

#include "EngineLib.h"

class MainMenuScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(MainMenuScript); }

	void Start() override;
	void Update() override;

public:
	explicit MainMenuScript(Button* listBtn[3]);
	~MainMenuScript() override;

private:
	void MyFunc();

	void OnPlay();
	void OnCredits();
	void OnQuit();

	Button* _listBtn[3];
	float speed = 1.0f;
	bool noir = true;
};

