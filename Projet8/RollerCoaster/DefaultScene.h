#pragma once

#include "EngineLib.h"

class DefaultScene : public IScene
{

public:
	string GetName() override;
	void GenerateContent() override;

};
