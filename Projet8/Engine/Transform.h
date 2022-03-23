#pragma once

enum class Space
{
	World,
    Self,
};


class Transform final : public EngineComponent
{

public:
    const char* GetType() override { return NAMEOF(Transform); }
    
    Transform();

    void Identity();
    void FromMatrix(D3DXMATRIX* pMat);
    void UpdateRotationFromVectors();
    void UpdateRotationFromQuaternion();
    void UpdateRotationFromMatrix();
    void UpdateMatrix();
    void Rotate(float pitch, float yaw, float roll, Space relativeTo = Space::Self);
    void RotatePitch(float angle, Space relativeTo = Space::Self);
    void RotateYaw(float angle, Space relativeTo = Space::Self);
    void RotateRoll(float angle, Space relativeTo = Space::Self);
    void RotateWorld(D3DXMATRIX* pMatrix);
    void RotateWorldX(float angle);
    void RotateWorldY(float angle);
    void RotateWorldZ(float angle);

    D3DXMATRIX GetMatrix() const { return matrix; }
    //bool Equals(Transform* other);

    D3DXVECTOR3 GetPosition() const { return position; }
    void SetPosition(D3DXVECTOR3 position);

    D3DXVECTOR3 GetScale() const { return scale; }
    void SetScale(D3DXVECTOR3 s);

    D3DXQUATERNION GetQuaternion() const { return quaternion; }
    void SetQuaternion(D3DXQUATERNION q);

    D3DXVECTOR3 GetRotation() const { return {quaternion.x, quaternion.y, quaternion.z}; }
    D3DXMATRIX GetRotationMatrix() const { return rotation; }

    D3DXVECTOR3 GetForward() const { return forward; }
    D3DXVECTOR3 GetRight() const { return right; }
    D3DXVECTOR3 GetUp() const { return up; }

private:
    D3DXMATRIX matrix;

    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;

    D3DXQUATERNION quaternion;
    D3DXMATRIX rotation;

    D3DXVECTOR3 forward;
    D3DXVECTOR3 right;
    D3DXVECTOR3 up;

};
