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
	list<MeshRenderer*> GetCube() { return  _cubes; }
	void MoveForward();
	MeshRenderer* PopFrontCube();
private :
	list<MeshRenderer*> _cubes = {};
	const float _spaceBetween = 3.0f;
	float _maxDistance = 100.0f;
	const float _step = 10;

	float _angleUp = 90;
	float _currentStep;

};

