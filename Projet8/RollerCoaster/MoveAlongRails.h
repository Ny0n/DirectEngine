#pragma once

#include "EngineLib.h"
#include "RailMaker.h"

class Cube;

class MoveAlongRails : public MonoBehaviour
{
    string GetType() override { return NAMEOF(MoveAlongRails); }

    void Start() override;
    void Update() override;

    ~MoveAlongRails() override;

public:
    Transform* GetTransfromWhithoutCursor() const { return _pTransformWhithoutCursor;}

    void Move();

private:
    list<MeshRenderer*> _cubes;
    list<MeshRenderer*> _toDelete;

    RailMaker* _pRailMaker;

    float _speed =25.0f;
    float _almostOnSpot = 1.0f;

    Transform* _pTransformWhithoutCursor;

    //Lerp
    D3DXQUATERNION _quat;
    D3DXQUATERNION _cubeQuat;
    int _nbStep = 0;

};

