#pragma once

#include "EngineLib.h"

class LionelScene :
    public IScene
{

public:
	string GetName() override;
	void GenerateContent() override;


};

