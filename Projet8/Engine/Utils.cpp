#include "pch.h"

void Utils::PrintError(string file, int line, LPCWSTR value)
{
	string strLine = to_string(line);

	const wstring tempFile(file.begin(), file.end());
	const wstring tempLine(strLine.begin(), strLine.end());

	OutputDebugStringW(tempFile.c_str());
	OutputDebugStringW(L":");
	OutputDebugStringW(tempLine.c_str());
	OutputDebugStringW(L" ");
	OutputDebugStringW(value);
	OutputDebugStringW(L"\n");
}

void Utils::Println(LPCWSTR value)
{
	OutputDebugStringW(value);
	OutputDebugStringW(L"\n");
}

void Utils::Println(wstring value)
{
	OutputDebugStringW(value.c_str());
	OutputDebugStringW(L"\n");
}

void Utils::Println(string value)
{
	value += "\n";
	const wstring temp(value.begin(), value.end());
	OutputDebugStringW(temp.c_str());
}

void Utils::PrintErr(string value)
{
	Println("WARNING: " + value);
}

void Utils::Println(int value)
{
	Println(to_string(value));
}

void Utils::Println(unsigned value)
{
	Println(to_string(value));
}

void Utils::Println(long value)
{
	Println(to_string(value));
}

void Utils::Println(unsigned long value)
{
	Println(to_string(value));
}

void Utils::Println(long long value)
{
	Println(to_string(value));
}

void Utils::Println(unsigned long long value)
{
	Println(to_string(value));
}

void Utils::Println(double value)
{
	Println(to_string(value));
}

void Utils::Println(float value)
{
	Println(to_string(value));
}

void Utils::Println(long double value)
{
	Println(to_string(value));
}

// **************************** //

float Utils::DistanceWithOutSquareRoot(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

float Utils::Distance(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

D3DXQUATERNION Utils::SLERP(const D3DXQUATERNION* a, const D3DXQUATERNION* b, const float t)
{
	D3DXQUATERNION r;
	float t_ = 1 - t;
	float Wa, Wb;
	float theta = acos(a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
	float sn = sin(theta);
	Wa = sinf(t_ * theta) / sn;
	Wb = sinf(t * theta) / sn;
	r.x = Wa * a->x + Wb * b->x;
	r.y = Wa * a->y + Wb * b->y;
	r.z = Wa * a->z + Wb * b->z;
	r.w = Wa * a->w + Wb * b->w;
	D3DXQuaternionNormalize(&r,&r);
	return r;
}

float Utils::GetRandomFloat(float lowBound, float highBound)
}
	return (f * (highBound - lowBound)) + lowBound;
	// return float in [lowBound, highBound] interval.
	float f = (rand() % 10000) * 0.0001f;
	// get random float in [0, 1] interval
		return lowBound;
	if (lowBound >= highBound) // bad input
{


void Utils::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max)
	{
{
		out->x = GetRandomFloat(min->x, max->x);
		out->y = GetRandomFloat(min->y, max->y);
		out->z = GetRandomFloat(min->z, max->z);
}
	}
