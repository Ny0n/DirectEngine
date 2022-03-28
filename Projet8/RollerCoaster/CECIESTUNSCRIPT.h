#pragma once
#include "EngineLib.h"

class CECIESTUNSCRIPT : public MonoBehaviour
{

public:
	string GetType() override { return NAMEOF(CECIESTUNSCRIPT); };
	void Update() override;

	explicit CECIESTUNSCRIPT(Image* image, Textbox* textbox);
	~CECIESTUNSCRIPT() override;

private:
	Image* _image;
	Textbox* _textbox;
	float speed = 1.0f;
	int x, y, z = 0;
};

