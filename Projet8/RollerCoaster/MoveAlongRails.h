#pragma once
#include "EngineLib.h"
#include "RailMaker.h"
class Cube;

class MoveAlongRails :
    public MonoBehaviour
{
public :
	string GetType() override { return NAMEOF(MoveAlongRails); }
    void Update() override;
    void Start() override;
    void Move();
    MoveAlongRails(){}
private:
    list<Cube*> _cubes;
    RailMaker* _rm;
    D3DXVECTOR3 _previousDir;
    float _speed = 70.0f;
    float _almostOnSpot = 2.0f;
};

