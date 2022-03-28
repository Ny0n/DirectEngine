#pragma once

#include "EngineLib.h"

class CECIESTUNSCRIPT : public MonoBehaviour
{
	string GetType() override { return NAMEOF(CECIESTUNSCRIPT); }

	void Start() override;
	void Update() override;

public:
	explicit CECIESTUNSCRIPT(Button* listBtn[3]);
	~CECIESTUNSCRIPT() override;

private:
	void MyFunc();

	void OnPlay();
	void OnCredits();
	void OnQuit();

	Button* _listBtn[3];
	float speed = 1.0f;
	bool noir = true;
};

