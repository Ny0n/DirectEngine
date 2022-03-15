#pragma once

#include "Component.h"

class Transform : public Component
{
public:
    const char* GetType() override { return NAMEOF(Transform); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }
    
    


public:
    Transform();

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

    D3DXQUATERNION GetQuaternion() { return quaternion; }
    void SetQuaternion(D3DXQUATERNION q);

    void SetPosition(D3DXVECTOR3 position);
    D3DXVECTOR3 GetPosition() { return position; };

    void SetScale(D3DXVECTOR3 s);
    D3DXVECTOR3 GetScale() { return scale; }

    D3DXMATRIX GetMatrix() { return matrix; }
    //bool Equals(Transform* other);
private :
    D3DXVECTOR3 scale;

    D3DXVECTOR3 forward;
    D3DXVECTOR3 right;
    D3DXVECTOR3 up;
    D3DXQUATERNION quaternion;
    D3DXMATRIX rotation;

    D3DXVECTOR3 position;

    D3DXMATRIX matrix;
};
