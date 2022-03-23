#pragma once

#include "EngineLib.h"

class DontDestroyOnLoad : public MonoBehaviour
{

public:
    const char* GetType() override { return NAMEOF(DontDestroyOnLoad); }

    void Start() override;

};
