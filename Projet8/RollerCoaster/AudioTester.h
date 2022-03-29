#pragma once

#include "EngineLib.h"

class AudioTester : public MonoBehaviour
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
