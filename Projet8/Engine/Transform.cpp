#include "pch.h"

Transform::Transform()
{
	Identity();
}

/**
 * \brief Default transform
 */
void Transform::Identity()
{
	_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //Default scale

	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	 //Default right vector (x axis)
	_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 //Default up vector (y axis)
	_forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f); //Default forward vector (z axis)

	D3DXQuaternionIdentity(&_quaternion); //Default quaternion

	D3DXMatrixRotationQuaternion(&_rotation, &_quaternion); //Default matrix rotation

	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //Default position

	D3DXMatrixIdentity(&_matrix);
}

void Transform::RotationIdentity()
{
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	 //Default right vector (x axis)
	_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 //Default up vector (y axis)
	_forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f); //Default forward vector (z axis)

	D3DXQuaternionIdentity(&_quaternion); //Default quaternion

	D3DXMatrixRotationQuaternion(&_rotation, &_quaternion); //Default matrix rotation
}

void Transform::SetRotationFromVectors(D3DXVECTOR3* right, D3DXVECTOR3* up, D3DXVECTOR3* forward)
{
	_rotation._11 = right->x;
	_rotation._12 = right->y;
	_rotation._13 = right->z;

	_rotation._21 = up->x;
	_rotation._22 = up->y;
	_rotation._23 = up->z;

	_rotation._31 = forward->x;
	_rotation._32 = forward->y;
	_rotation._33 = forward->z;

	D3DXQuaternionRotationMatrix(&_quaternion, &_rotation);
	UpdateMatrix();
}

void Transform::UpdateRotationFromQuaternion()
{
	D3DXMatrixRotationQuaternion(&_rotation, &_quaternion);

	//change axis value
	//x axis
	_right.x = _rotation._11;
	_right.y = _rotation._12;
	_right.z = _rotation._13;

	//y axis
	_up.x = _rotation._21;
	_up.y = _rotation._22;
	_up.z = _rotation._23;

	//z axis
	_forward.x = _rotation._31;
	_forward.y = _rotation._32;
	_forward.z = _rotation._33;

	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	D3DXMATRIX matScale,matTranslate;

	_matrix = _rotation;

	D3DXMatrixScaling(&matScale, _scale.x, _scale.y, _scale.z);
	_matrix *= matScale;

	D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);
	_matrix *= matTranslate;
}

void Transform::Rotate(float pitch, float yaw, float roll, Space relativeTo)
{
	D3DXQUATERNION quatRot;
	D3DXQuaternionIdentity(&quatRot);

	D3DXVECTOR3 xAxis;
	D3DXVECTOR3 yAxis;
	D3DXVECTOR3 zAxis;

	switch (relativeTo)
		{
		case Space::World:
			{
				xAxis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				yAxis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				zAxis = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			} break;
		case Space::Self:
			{
				xAxis = _right;
				yAxis = _up;
				zAxis = _forward;
			} break;
		case Space::Custom:
			{
				xAxis = _customRight;
				yAxis = _customUp;
				zAxis = _customForward;
			}break;
	}
	

	D3DXQUATERNION quat;

	//rotate x axis
	D3DXQuaternionRotationAxis(&quat, &xAxis,D3DXToRadian(pitch));
	quatRot *= quat;

	//rotate y axis
	D3DXQuaternionRotationAxis(&quat, &yAxis, D3DXToRadian(yaw));
	quatRot *= quat;

	//rotate z axis
	D3DXQuaternionRotationAxis(&quat, &zAxis, D3DXToRadian(roll));
	quatRot *= quat;

	//add the new rotation to the actual one
	_quaternion *= quatRot;

	//create a new rotation matrix
	D3DXMatrixRotationQuaternion(&_rotation, &_quaternion);

	//change axis value
	//x axis
	_right.x = _rotation._11;
	_right.y = _rotation._12;
	_right.z = _rotation._13;

	//y axis
	_up.x = _rotation._21;
	_up.y = _rotation._22;
	_up.z = _rotation._23;

	//z axis
	_forward.x = _rotation._31;
	_forward.y = _rotation._32;
	_forward.z = _rotation._33;

	UpdateMatrix();
}

/**
 * \brief rotate on the x axis
 * \param angle in degree
 */
void Transform::RotatePitch(float angle, Space relativeTo)
{
	Rotate(angle, 0, 0, relativeTo);
}

/**
 * \brief rotate on the y axis
 * \param angle in degree
 */
void Transform::RotateYaw(float angle, Space relativeTo)
{
	Rotate(0, angle, 0, relativeTo);
}

/**
 * \brief rotate on the z axis
 * \param angle in degree
 */
void Transform::RotateRoll(float angle, Space relativeTo)
{
	Rotate(0, 0, angle, relativeTo);
}

void Transform::AddRotationMatrix(D3DXMATRIX p)
{

	D3DXQUATERNION quat;

	_rotation *= p;
	D3DXQuaternionRotationMatrix(&quat, &_rotation);
	_quaternion *= quat;

	_right.x = _rotation._11;
	_right.y = _rotation._12;
	_right.z = _rotation._13;

	//y axis
	_up.x = _rotation._21;
	_up.y = _rotation._22;
	_up.z = _rotation._23;

	//z axis
	_forward.x = _rotation._31;
	_forward.y = _rotation._32;
	_forward.z = _rotation._33;

	UpdateMatrix();
}

void Transform::SetQuaternion(D3DXQUATERNION quat)
{
	_quaternion = quat;
	UpdateRotationFromQuaternion();
}

void Transform::SetCustomAxis(D3DXVECTOR3 right, D3DXVECTOR3 up, D3DXVECTOR3 forward)
{
	_customForward = forward;
	_customRight = right;
	_customUp = up;
}

void Transform::SetPosition(D3DXVECTOR3 pos)
{
	_position = pos;
	UpdateMatrix();
}

void Transform::SetScale(D3DXVECTOR3 s)
{
	_scale = s;
	UpdateMatrix();
}


