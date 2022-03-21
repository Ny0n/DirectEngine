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
	static void DeleteList(list<T*>* list);
	static float DistanceWithOutSquareRoot(D3DXVECTOR3 a, D3DXVECTOR3 b);
	static float Distance(D3DXVECTOR3 a, D3DXVECTOR3 b) ;
};

template <typename T>
bool Utils::Contains(list<T*>* list, T* value)
{
	return (find(list->begin(), list->end(), value) != list->end());
}

template <typename T>
void Utils::DeleteList(list<T*>* list)
{
	for (auto element : *list)
	{
		delete(element);
	}

	list->clear();
}

inline float Utils::DistanceWithOutSquareRoot(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

inline float Utils::Distance(D3DXVECTOR3 a, D3DXVECTOR3 b) 
{
	return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
