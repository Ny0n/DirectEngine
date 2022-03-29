#pragma once

#include "EngineLib.h"
#include "Tile.h"

class RailMaker : public MonoBehaviour
{
	string GetType() override { return NAMEOF(RailMaker); }

	void Start() override;
	void Update() override;

public:
	explicit RailMaker() {}
	~RailMaker() override;
	list<Tile*> GetTiles() { return  _tiles; }
	void MoveForward();
	Tile* PopFrontCube();
private :
	list<Tile*> _tiles;
	const float _spaceBetween = 3.0f;
	int _maxDistance = 50;
	const float _step = 10;

	float _angleUp = 90;
	float _currentStepUp;

	float _angleRight = 90;
	float _currentStepRight;
};

