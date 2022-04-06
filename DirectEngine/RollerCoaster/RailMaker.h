#pragma once

#include "EngineLib.h"


class RailMaker : public MonoBehaviour
{
	string GetType() override { return NAMEOF(RailMaker); }

	void Start() override;
	void Update() override;

	~RailMaker() override;

public:
	list<MeshRenderer*> GetCube() { return  _cubes; }
	list<GameObject*> GetTarget() { return  _targets; }

	void SetTarget(list<GameObject*> targets) { _targets = targets; }

	void CreateLevelStep();

	MeshRenderer* PopFrontCube();

private :
	list<MeshRenderer*> _cubes = {};
	list<GameObject*> _targets={};

	const float _spaceBetween = 3.0f;
	int _maxDistance = 50;
	const float _step = 10;

	float _angleUp;
	float _currentStepUp;

	float _angleRight;
	float _currentStepRight;
};

