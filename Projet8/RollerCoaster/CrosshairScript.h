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
	void OnEnable() override;
	void OnDisable() override;

	Image* _img;
};

