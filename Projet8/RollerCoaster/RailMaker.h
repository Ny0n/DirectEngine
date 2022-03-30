#pragma once

#include "EngineLib.h"


class RailMaker : public MonoBehaviour
{
	string GetType() override { return NAMEOF(RailMaker); }

	void Start() override;
	void Update() override;

public:

	explicit RailMaker() {}
	~RailMaker() override;

	list<MeshRenderer*> GetCube() { return  _cubes; }
	list<GameObject*> GetTarget() { return  _target; }
	void SetTarget(list<GameObject*> targets) { _target = targets; }

	void MoveForward();

	MeshRenderer* PopFrontCube();
private :
	list<MeshRenderer*> _cubes = {};
	list<GameObject*> _target={};

	const float _spaceBetween = 3.0f;
	int _maxDistance = 50;
	const float _step = 10;

	float _angleUp = 90;
	float _currentStepUp;

	float _angleRight = 90;
	float _currentStepRight;
};

