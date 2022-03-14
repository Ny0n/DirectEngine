#pragma once

#include "Component.h"

struct Vector3
{
    float x, y, z;
};

struct MATRIX
{
    float x, y, z;
};

struct QUATERNION
{
    float x, y, z;
};

class Transform : public Component
{
public:
	ComponentType GetType() override { return ComponentType::transform; }
    
    D3DXVECTOR3 scale;

    D3DXVECTOR3 forward;
    D3DXVECTOR3 right;
    D3DXVECTOR3 up;
    D3DXQUATERNION quaternion;
    D3DXMATRIX rotation;

    D3DXVECTOR3 position;

    D3DXMATRIX matrix;


public:
    void Identity();
    void FromMatrix(D3DXMATRIX* pMat);
    void UpdateRotationFromVectors();
    void UpdateRotationFromQuaternion();
    void UpdateRotationFromMatrix();
    void UpdateMatrix();
    void Rotate(float pitch, float yaw, float roll);
    void RotatePitch(float angle);
    void RotateYaw(float angle);
    void RotateRoll(float angle);
    void RotateWorld(D3DXMATRIX* pMatrix);
    void RotateWorldX(float angle);
    void RotateWorldY(float angle);
    void RotateWorldZ(float angle);

};
