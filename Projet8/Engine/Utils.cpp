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

float Utils::DistanceWithOutSquareRoot(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

float Utils::Distance(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
