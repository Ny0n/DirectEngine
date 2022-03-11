#pragma once

#include <string>

#include "framework.h"

class Utils
{

public:
	static void println(std::string s)
	{
		s += "\n";
		std::wstring temp(s.begin(), s.end());
		LPCWSTR lpcwstr = temp.c_str();
		OutputDebugStringW(lpcwstr);
	}

};
