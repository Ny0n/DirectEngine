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
};

