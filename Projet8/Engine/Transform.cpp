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

void Transform::FromMatrix(D3DXMATRIX* pMat)
{
}

void Transform::UpdateRotationFromVectors()
{
}

void Transform::UpdateRotationFromQuaternion()
{
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

void Transform::Rotate(float pitch, float yaw, float roll)
{
	D3DXQUATERNION quatRot;
	D3DXQuaternionIdentity(&quatRot);

	D3DXQUATERNION quat;

	//rotate x axis
	D3DXQuaternionRotationAxis(&quat, &right,D3DXToRadian(pitch));
	quatRot *= quat;

	//rotate y axis
	D3DXQuaternionRotationAxis(&quat, &up, D3DXToRadian(yaw));
	quatRot *= quat;

	//rotate z axis
	D3DXQuaternionRotationAxis(&quat, &forward, D3DXToRadian(roll));
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
void Transform::RotatePitch(float angle)
{
	Rotate(angle, 0, 0);
}

/**
 * \brief rotate on the y axis
 * \param angle in degree
 */
void Transform::RotateYaw(float angle)
{
	Rotate(0, angle, 0);
}

/**
 * \brief rotate on the z axis
 * \param angle in degree
 */
void Transform::RotateRoll(float angle)
{
	Rotate(0, 0, angle);
}

void Transform::RotateWorld(D3DXMATRIX* pMatrix)
{
}

void Transform::RotateWorldX(float angle)
{
}

void Transform::RotateWorldY(float angle)
{
}

void Transform::RotateWorldZ(float angle)
{
}

void Transform::SetQuaternion(D3DXQUATERNION quat)
{
	quaternion = quat;
	UpdateMatrix();
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

//bool Transform::Equals(Transform* other)
//{ 
//	if (position.x != other->position.x &&
//		position.y != other->position.y &&
//		position.z != other->position.z &&
//		quaternion.x != other->quaternion.x &&
//		quaternion.y != other->quaternion.y &&
//		quaternion.z != other->quaternion.z &&
//		quaternion.w != other->quaternion.w)
//		return false;
//	for (int i = 0; i < sizeof(rotation) / sizeof(rotation[0]); i++)
//		if (rotation[i] != other->rotation[i]) 
//		{
//			return false;
//		}
//	for(int i = 0 ; i < sizeof(matrix)/sizeof(matrix[0]); i++)
//		if(matrix[i] != other->matrix[i])
//		{
//			return false;
//		}
//	return true;
//}
