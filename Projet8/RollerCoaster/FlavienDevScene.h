#pragma once

#include "EngineLib.h"

class FlavienDevScene : public IScene
{

public:
	string GetName() override;
	void GenerateContent() override;

};

