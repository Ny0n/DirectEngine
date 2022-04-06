#pragma once

#include "EngineLib.h"

class MenuScene : public IScene
{

public:
	string GetName() override;
	void GenerateContent() override;

};
