#pragma once

#include "EngineLib.h"

class CECIESTUNSCRIPT : public MonoBehaviour
{
	string GetType() override { return NAMEOF(CECIESTUNSCRIPT); }

	void Start() override;
	void Update() override;

public:
	CECIESTUNSCRIPT();
	explicit CECIESTUNSCRIPT(Image* image);
	~CECIESTUNSCRIPT() override;

private:
	Image* _image;
	float speed = 1.0f;

};

