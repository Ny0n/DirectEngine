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
    ~MoveAlongRails() override;

    Transform* GetTransfromWhithoutCursor() const { return transformWhithoutCursor;}
    void Move();

private:
    list<Tile*> _tiles;
    list<Tile*> _toDelete;
    RailMaker* _rm;
    D3DXVECTOR3 _previousDir;
    float _speed = 25.0f;
    float _almostOnSpot = 1.0f;
    Transform* transformWhithoutCursor;

    //Lerp
    D3DXQUATERNION quat;
    D3DXQUATERNION cubeQuat;
    int NbreStep = 0;

};

