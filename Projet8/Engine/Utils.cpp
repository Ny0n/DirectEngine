#include "pch.h"

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
