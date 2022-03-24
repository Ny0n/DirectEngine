#pragma once
#include "EngineLib.h"

class CECIESTUNSCRIPT : public MonoBehaviour
{

public:
	string GetType() override { return NAMEOF(CECIESTUNSCRIPT); };
	void Update() override;

	explicit CECIESTUNSCRIPT(Image* image);
	~CECIESTUNSCRIPT() override;

private:
	Image* _image;
	float speed = 1.0f;
};

