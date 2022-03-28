#pragma once

#include "EngineLib.h"

#include "Cube.h"

class RailMaker : public MonoBehaviour
{
	string GetType() override { return NAMEOF(RailMaker); }

	void Start() override;
	void Update() override;

public:
	explicit RailMaker() {}

	void Turn(float rotate);
	list<Cube*> GetCube() { return  _cubes; }
	void MoveForward();
	Cube* PopFrontCube();

private :
	list<Cube*> _cubes = {};
	const float _spaceBetween = 5.0f;
	float _maxDistance = 100.0f;
	const float _step = 10;

};

