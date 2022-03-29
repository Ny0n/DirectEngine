#pragma once

#include "EngineLib.h"

class CrosshairScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(CrosshairScript); }

	void Start() override;
	void Update() override;

public:
	CrosshairScript(Image* img);
	~CrosshairScript() override;

private:
	Image* _img;
};

