#pragma once

#include "EngineLib.h"
#include "SceneSingleton.h"

class BackgroundMusic : public SceneSingleton<BackgroundMusic>
{
	string GetType() override { return NAMEOF(BackgroundMusic); }

	void Start() override;

public:
	BackgroundMusic();
	~BackgroundMusic() override;

	AudioSource* source = nullptr;

};
