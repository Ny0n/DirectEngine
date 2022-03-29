#pragma once
#include "EngineLib.h"

class Tile
{
public :
	MeshRenderer* _cube;
	GameObject* _target;
	Tile(MeshRenderer* cube, GameObject* target) { _cube = cube; _target = target; }

	~Tile() { }

private:
};

