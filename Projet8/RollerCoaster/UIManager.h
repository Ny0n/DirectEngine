#pragma once

#include "EngineLib.h"

class UIManager : public MonoBehaviour
{
	string GetType() override { return NAMEOF(UIManager); }

	void Start() override;
	void Update() override;

public:
	explicit UIManager(Button* listBtn[3]);
	~UIManager() override;

private:
	void MyFunc();

	void OnPlay();
	void OnCredits();
	void OnQuit();

	Button* _listBtn[3];
	float speed = 1.0f;
	bool noir = true;
};

