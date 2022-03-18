#include "pch.h"

void Utils::Println(string s)
{
	s += "\n";
	wstring temp(s.begin(), s.end());
	LPCWSTR lpcwstr = temp.c_str();
	OutputDebugStringW(lpcwstr);
}
