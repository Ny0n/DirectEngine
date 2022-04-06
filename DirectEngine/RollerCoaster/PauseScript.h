#pragma once

#include "EngineLib.h"

class PauseScript : public MonoBehaviour
{
	string GetType() override { return NAMEOF(PauseScript); }

	void Start() override;
	void Update() override;

public:
	PauseScript();
	~PauseScript() override;

	void OnEnable() override;
	void OnDisable() override;

	bool isPaused = false;
};
