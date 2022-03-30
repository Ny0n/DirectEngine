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

D3DXVECTOR4 Utils::GetVec4FromQuat(D3DXQUATERNION* q)
{
	D3DXVECTOR4 vector4;
	vector4.x = q->x;
	vector4.z = q->z;
	vector4.y = q->y;
	vector4.w = q->w;
	return  vector4;
}

D3DXQUATERNION Utils::GetQuatFromVec4(D3DXVECTOR4* q)
{
	D3DXQUATERNION quat;
	quat.x = q->x;
	quat.z = q->z;
	quat.y = q->y;
	quat.w = q->w;
	return  quat;
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

{
	if (lowBound >= highBound) // bad input
		return lowBound;
	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f;
	// return float in [lowBound, highBound] interval.
	return (f * (highBound - lowBound)) + lowBound;
}

void Utils::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	{
		out->x = GetRandomFloat(min->x, max->x);
		out->y = GetRandomFloat(min->y, max->y);
		out->z = GetRandomFloat(min->z, max->z);
	}
}

//
//// Returns true if sphere s intersects triangle ABC, false otherwise.
//// The point p on abc closest to the sphere center is also returned
//inline bool TestSphereTriangle(D3DXVECTOR2 s,float r, D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, Point& p)
//{
//	// Find point P on triangle ABC closest to sphere center
//	p = ClosestPtPointTriangle(s, a, b, c);
//	// Sphere and triangle intersect if the (squared) distance from sphere
//// center to point p is less than the (squared) sphere radius
//	D3DXVECTOR2 v = p - s;
//	return D3DXVec2Dot(&v, &v) <= r * r;
//}
//D3DXVECTOR2 ClosestPtPointTriangle(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c)
//{
//	// Check if P in vertex region outside A
//	D3DXVECTOR2 ab = b - a;
//	D3DXVECTOR2 ac = c - a;
//	D3DXVECTOR2 ap = p - a;
//	float d1 = D3DXVec2Dot(&ab, &ap);
//	float d2 = D3DXVec2Dot(&ac, &ap);
//	if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)
//	// Check if P in vertex region outside B
//	D3DXVECTOR2 bp = p - b;
//	float d3 = D3DXVec2Dot(&ab, &ap);
//	float d4 = D3DXVec2Dot(&ab, &ap);
//	if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)
//	// Check if P in edge region of AB, if so return projection of P onto AB
//	float vc = d1 * d4 - d3 * d2;
//	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
//		float v = d1 / (d1 - d3);
//		return a + v * ab; // barycentric coordinates (1-v,v,0)
//	}
//	// Check if P in vertex region outside C
//	D3DXVECTOR2 cp = p - c;
//	float d5 = D3DXVec2Dot(&ab, &cp);
//	float d6 = D3DXVec2Dot(&ac, &cp);
//	if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)
//		// Check if P in edge region of AC, if so return projection of P onto AC
//		float vb = d5 * d2 - d1 * d6;
//	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
//		float w = d2 / (d2 - d6);
//		return a + w * ac; // barycentric coordinates (1-w,0,w)
//	}
//	// Check if P in edge region of BC, if so return projection of P onto BC
//	float va = d3 * d6 - d5 * d4;
//	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
//		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
//		return b + w * (c - b); // barycentric coordinates (0,1-w,w)
//	}
//	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
//	float denom = 1.0f / (va + vb + vc);
//	float v = vb * denom;
//	float w = vc * denom;
//	return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f-v-w
//}
