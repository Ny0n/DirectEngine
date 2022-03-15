﻿#include "pch.h"

#include "Transform.h"

#include "Utils.h"



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

	//Display the D3DX Matrix
	/*Utils::Println("11: " + to_string(rotation._11) + "|12: " + to_string(rotation._12) + "|13: " + to_string(rotation._13) + "|14: " + to_string(rotation._14) + "\n" +
					"21: " + to_string(rotation._21) + "|22: " + to_string(rotation._22) + "|23: " + to_string(rotation._23) + "|24: " + to_string(rotation._24) + "\n" +
					"31: " + to_string(rotation._31) + "|32: " + to_string(rotation._32) + "|33: " + to_string(rotation._33) + "|34: " + to_string(rotation._34) + "\n" +
					"41: " + to_string(rotation._41) + "|42: " + to_string(rotation._42) + "|43: " + to_string(rotation._43) + "|44: " + to_string(rotation._44) + "\n");*/


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
}

void Transform::Rotate(float pitch, float yaw, float roll)
{
	D3DXQUATERNION quatRot;
	D3DXQuaternionIdentity(&quatRot);

	D3DXQUATERNION quat;
	D3DXQuaternionIdentity(&quatRot);

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
	D3DXMATRIX matrixRot;
	D3DXMatrixRotationQuaternion(&matrixRot, &quaternion);

	//change axis value
	//x axis
	right.x = matrixRot._11;
	right.y = matrixRot._12;
	right.z = matrixRot._13;

	//y axis
	up.x = matrixRot._21;
	up.y = matrixRot._22;
	up.z = matrixRot._23;

	//z axis
	forward.x = matrixRot._31;
	forward.y = matrixRot._32;
	forward.z = matrixRot._33;
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