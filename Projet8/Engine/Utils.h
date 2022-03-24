#pragma once

class Utils final
{

public:
	Utils() = delete;

	static void Println(LPCWSTR value);
	static void Println(wstring value);
	static void Println(string value);
	static void Println(int value);
	static void Println(unsigned value);
	static void Println(long value);
	static void Println(unsigned long value);
	static void Println(long long value);
	static void Println(unsigned long long value);
	static void Println(double value);
	static void Println(float value);
	static void Println(long double value);

	template<typename T>
	static bool Contains(list<T*>* list, T* value);
	template<typename T>
	static bool Contains(list<T>* list, T value);

	template<typename T>
	static void DeleteList(list<T*> listIn);
	template <typename K, typename V>
	static void DeleteMap(map<K*, V*> mapIn);
	template <typename K, typename V>
	static void DeleteMapFirst(map<K*, V> mapIn);
	template <typename K, typename V>
	static void DeleteMapSecond(map<K, V*> mapIn);

	static float DistanceWithOutSquareRoot(D3DXVECTOR3 a, D3DXVECTOR3 b);
	static float Distance(D3DXVECTOR3 a, D3DXVECTOR3 b) ;
};

#include "Utils.tpp"
