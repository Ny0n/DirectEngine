#pragma once

#include "EngineLib.h"

class CECINESTPASUNSCRIPT : public MonoBehaviour
{
	string GetType() override { return NAMEOF(CECINESTPASUNSCRIPT); }

	void Start() override;
	void Update() override;

public:
	CECINESTPASUNSCRIPT(Image *img);
	~CECINESTPASUNSCRIPT() override;

private:
	Image* _img;
};
