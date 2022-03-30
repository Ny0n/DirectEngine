#pragma once

enum class Space
{
	World,
    Self,
    Custom,
};

class Transform final : public EngineComponent
{
    string GetType() override { return NAMEOF(Transform); }

public:
    Transform();

    void Identity();
    void RotationIdentity();
    void FromMatrix(D3DXMATRIX* pMat);
    void SetRotationFromVectors(D3DXVECTOR3* right, D3DXVECTOR3* up, D3DXVECTOR3* forward);
    void UpdateRotationFromQuaternion();
    void UpdateRotationFromMatrix();
    void UpdateMatrix();
    void Rotate(float pitch, float yaw, float roll, Space relativeTo = Space::Self);
    void RotatePitch(float angle, Space relativeTo = Space::Self);
    void RotateYaw(float angle, Space relativeTo = Space::Self);
    void RotateRoll(float angle, Space relativeTo = Space::Self);
    void RotateWorld(D3DXMATRIX* pMatrix);
    void AddRotationMatrix(D3DXMATRIX p);

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

    void SetCustomAxis(D3DXVECTOR3 right, D3DXVECTOR3 up, D3DXVECTOR3 forward);

private:
    D3DXMATRIX matrix;

    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;

    D3DXQUATERNION quaternion;
    D3DXMATRIX rotation;

    D3DXVECTOR3 forward;
    D3DXVECTOR3 right;
    D3DXVECTOR3 up;


    D3DXVECTOR3 customForward = D3DXVECTOR3(1,0,0);
    D3DXVECTOR3 customRight = D3DXVECTOR3(0, 1, 0);
    D3DXVECTOR3 customUp = D3DXVECTOR3(0, 0, 1);

};
