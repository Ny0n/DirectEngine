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
    void Init();

private:
    list<MeshRenderer*> _cubes;
    RailMaker* _rm;
    D3DXVECTOR3 _previousDir;
    float _speed =40.0f;
    float _almostOnSpot = 3.0f;
    Transform* transformWhithoutCursor;

    //Lerp
    D3DXQUATERNION quat;
    D3DXQUATERNION cubeQuat;
    int NbreStep = 0;
    bool initialiased = false;

};

