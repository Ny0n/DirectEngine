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
    void SetRotationFromVectors(D3DXVECTOR3* right, D3DXVECTOR3* up, D3DXVECTOR3* forward);
    void UpdateRotationFromQuaternion();
    void UpdateMatrix();
    void Rotate(float pitch, float yaw, float roll, Space relativeTo = Space::Self);
    void RotatePitch(float angle, Space relativeTo = Space::Self);
    void RotateYaw(float angle, Space relativeTo = Space::Self);
    void RotateRoll(float angle, Space relativeTo = Space::Self);
    void AddRotationMatrix(D3DXMATRIX p);

    D3DXMATRIX GetMatrix() const { return _matrix; }
    //bool Equals(Transform* other);

    D3DXVECTOR3 GetPosition() const { return _position; }
    void SetPosition(D3DXVECTOR3 position);

    D3DXVECTOR3 GetScale() const { return _scale; }
    void SetScale(D3DXVECTOR3 s);

    D3DXQUATERNION GetQuaternion() const { return _quaternion; }
    void SetQuaternion(D3DXQUATERNION q);

    D3DXVECTOR3 GetRotation() const { return {_quaternion.x, _quaternion.y, _quaternion.z}; }
    D3DXMATRIX GetRotationMatrix() const { return _rotation; }

    D3DXVECTOR3 GetForward() const { return _forward; }
    D3DXVECTOR3 GetRight() const { return _right; }
    D3DXVECTOR3 GetUp() const { return _up; }

    void SetCustomAxis(D3DXVECTOR3 right, D3DXVECTOR3 up, D3DXVECTOR3 forward);

private:
    D3DXMATRIX _matrix;

    D3DXVECTOR3 _position;
    D3DXVECTOR3 _scale;

    D3DXQUATERNION _quaternion;
    D3DXMATRIX _rotation;

    D3DXVECTOR3 _forward;
    D3DXVECTOR3 _right;
    D3DXVECTOR3 _up;


    D3DXVECTOR3 _customForward = D3DXVECTOR3(1,0,0);
    D3DXVECTOR3 _customRight = D3DXVECTOR3(0, 1, 0);
    D3DXVECTOR3 _customUp = D3DXVECTOR3(0, 0, 1);

};
