#pragma once
#include "EngineLib.h"
#include "Cube.h"

class RailMaker :
	public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(RailMaker); }
	//ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	explicit RailMaker() {}

	void Update() override;
	void Start() override;
	void Turn(float rotate);
	list<MeshRenderer*> GetCube() { return  _cubes; }
	void MoveForward();
	MeshRenderer* PopFrontCube();
private :
	list<MeshRenderer*> _cubes = {};
	const float _spaceBetween = 3.0f;
	float _maxDistance = 10.0f;
	const float _step = 10;

	float _angleUp = 90;
	float _currentStep;

};

