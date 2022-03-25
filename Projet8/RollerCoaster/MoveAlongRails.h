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
    ~MoveAlongRails() override;
    Transform GetTransfromWhithoutCursor() const { return *transformWhithoutCursor;}
private:
    list<Cube*> _cubes;
    RailMaker* _rm;
    D3DXVECTOR3 _previousDir;
    float _speed = 30.0f;
    float _almostOnSpot = 0.5f;
    Transform* transformWhithoutCursor;

    //Lerp
    D3DXQUATERNION quat;
    D3DXQUATERNION cubeQuat;
    int NbreStep = 0;
};

