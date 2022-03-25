#pragma once

#include "EngineLib.h"

class DontDestroyOnLoad : public MonoBehaviour
{

public:
	string GetType() override { return NAMEOF(DontDestroyOnLoad); }

    void Start() override;

};
