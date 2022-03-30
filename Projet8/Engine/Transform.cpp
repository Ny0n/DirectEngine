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
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //Default scale


	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	 //Default right vector (x axis)
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 //Default up vector (y axis)
	forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f); //Default forward vector (z axis)

	D3DXQuaternionIdentity(&quaternion); //Default quaternion

	D3DXMatrixRotationQuaternion(&rotation, &quaternion); //Default matrix rotation


	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //Default position

	D3DXMatrixIdentity(&matrix);
}

void Transform::RotationIdentity()
{
	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	 //Default right vector (x axis)
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 //Default up vector (y axis)
	forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f); //Default forward vector (z axis)

	D3DXQuaternionIdentity(&quaternion); //Default quaternion

	D3DXMatrixRotationQuaternion(&rotation, &quaternion); //Default matrix rotation
}


void Transform::FromMatrix(D3DXMATRIX* pMat)
{
}

void Transform::SetRotationFromVectors(D3DXVECTOR3* right, D3DXVECTOR3* up, D3DXVECTOR3* forward)
{
	rotation._11 = right->x;
	rotation._12 = right->y;
	rotation._13 = right->z;

	rotation._21 = up->x;
	rotation._22 = up->y;
	rotation._23 = up->z;

	rotation._31 = forward->x;
	rotation._32 = forward->y;
	rotation._33 = forward->z;

	D3DXQuaternionRotationMatrix(&quaternion, &rotation);
	UpdateMatrix();
}

void Transform::UpdateRotationFromQuaternion()
{
	D3DXMatrixRotationQuaternion(&rotation, &quaternion);

	//change axis value
	//x axis
	right.x = rotation._11;
	right.y = rotation._12;
	right.z = rotation._13;

	//y axis
	up.x = rotation._21;
	up.y = rotation._22;
	up.z = rotation._23;

	//z axis
	forward.x = rotation._31;
	forward.y = rotation._32;
	forward.z = rotation._33;

	UpdateMatrix();
}

void Transform::UpdateRotationFromMatrix()
{
}

void Transform::UpdateMatrix()
{
	matrix = rotation;
	D3DXMATRIX matScale,matTranslate;

	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	matrix *= matScale;
	D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
	matrix *= matTranslate;
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
				xAxis = right;
				yAxis = up;
				zAxis = forward;
			} break;
		case Space::Custom:
			{
				xAxis = customRight;
				yAxis = customUp;
				zAxis = customForward;
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
	quaternion *= quatRot;

	//create a new rotation matrix
	D3DXMatrixRotationQuaternion(&rotation, &quaternion);

	//change axis value
	//x axis
	right.x = rotation._11;
	right.y = rotation._12;
	right.z = rotation._13;

	//y axis
	up.x = rotation._21;
	up.y = rotation._22;
	up.z = rotation._23;

	//z axis
	forward.x = rotation._31;
	forward.y = rotation._32;
	forward.z = rotation._33;

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

void Transform::RotateWorld(D3DXMATRIX* pMatrix)
{
}

void Transform::AddRotationMatrix(D3DXMATRIX p)
{
	rotation *= p;
	D3DXQUATERNION quat;
	D3DXQuaternionRotationMatrix(&quat, &rotation);
	quaternion *= quat;
	right.x = rotation._11;
	right.y = rotation._12;
	right.z = rotation._13;

	//y axis
	up.x = rotation._21;
	up.y = rotation._22;
	up.z = rotation._23;

	//z axis
	forward.x = rotation._31;
	forward.y = rotation._32;
	forward.z = rotation._33;

	UpdateMatrix();
}

void Transform::SetQuaternion(D3DXQUATERNION quat)
{
	quaternion = quat;
	UpdateRotationFromQuaternion();
}

void Transform::SetCustomAxis(D3DXVECTOR3 right, D3DXVECTOR3 up, D3DXVECTOR3 forward)
{
	customForward = forward;
	customRight = right;
	customUp = up;
}

void Transform::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
	UpdateMatrix();
}

void Transform::SetScale(D3DXVECTOR3 s)
{
	scale = s;
	UpdateMatrix();
}


