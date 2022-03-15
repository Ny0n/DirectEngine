#pragma once

#include "EngineLib.h"

class DefaultScene : public Scene
{

public:
	~DefaultScene();
	DefaultScene();

private:
	static void FreeMemory(list<GameObject*> listGo);
	
};

