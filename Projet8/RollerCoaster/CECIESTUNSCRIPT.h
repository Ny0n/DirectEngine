#pragma once

#include "EngineLib.h"

class CECIESTUNSCRIPT : public MonoBehaviour
{
	string GetType() override { return NAMEOF(CECIESTUNSCRIPT); }

	void Start() override;
	void Update() override;

public:
	CECIESTUNSCRIPT();
	explicit CECIESTUNSCRIPT(Button* button);
	~CECIESTUNSCRIPT() override;

private:
	void MyFunc();
	Button* _button;
	float speed = 1.0f;

};

