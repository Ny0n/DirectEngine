#pragma once

#include "EngineLib.h"

class DontDestroyOnLoad : public MonoBehaviour
{
	string GetType() override { return NAMEOF(DontDestroyOnLoad); }

	void Start() override;

};
