#pragma once

#include "EngineLib.h"

class GameScene : public IScene
{

public:
	string GetName() override;
	void GenerateContent() override;

};
