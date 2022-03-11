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
	Vector3 position;

	QUATERNION quaternion;
	MATRIX rotation;

	Vector3 scale;
	Vector3 forward;
	Vector3 right;
	Vector3 up;

	MATRIX matrix;

};
