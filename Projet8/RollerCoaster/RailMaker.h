#pragma once
#include "EngineLib.h"
#include "Cube.h"

class RailMaker :
    public MonoBehaviour
{
public:
	const char* GetType() override { return NAMEOF(RailMaker); }
	//ComponentCategory GetCategory() override { return ComponentCategory::behaviour; }

	explicit RailMaker(Scene* s) { scene = s; }

	void Update() override;
	void Start() override;
	void Turn(float rotate);
	void MoveForward();
private :
	list<Cube*> cubes = {};
	const float _spaceBetween = 5.0f;
	 float _maxDistance = 100.0f;
	const float _step = 10;
	Scene* scene;
};

