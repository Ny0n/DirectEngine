#pragma once

#include "EngineLib.h"
#include "SceneSingleton.h"

class AudioTester : public SceneSingleton<AudioTester>
{
	string GetType() override { return NAMEOF(AudioTester); }

	void Start() override;
	void Update() override;

public:
	AudioTester();
	~AudioTester() override;

private:
	AudioSource* _source = nullptr;

};
