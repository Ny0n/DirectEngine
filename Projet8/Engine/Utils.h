#pragma once

class Utils
{

public:
	static void Println(string s)
	{
		s += "\n";
		wstring temp(s.begin(), s.end());
		LPCWSTR lpcwstr = temp.c_str();
		OutputDebugStringW(lpcwstr);
	}

	template<typename T>
	static bool Contains(list<T*>* list, T* value)
	{
		return (find(list->begin(), list->end(), value) != list->end());
	}

};
