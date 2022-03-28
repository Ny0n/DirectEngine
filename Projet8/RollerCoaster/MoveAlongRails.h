#pragma once

#include "EngineLib.h"

#include "RailMaker.h"

class Cube;

class MoveAlongRails : public MonoBehaviour
{
    string GetType() override { return NAMEOF(MoveAlongRails); }

    void Start() override;
    void Update() override;

public:
    MoveAlongRails(){}

    void Move();

private:
    list<Cube*> _cubes;
    RailMaker* _rm;
    D3DXVECTOR3 _previousDir;
    float _speed = 70.0f;
    float _almostOnSpot = 2.0f;

};

