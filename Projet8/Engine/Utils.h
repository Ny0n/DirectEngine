#pragma once

class Utils
{

public:
	static void Println(string s);

	template<typename T>
	static bool Contains(list<T*>* list, T* value);

	template<typename T>
	static void DeleteList(list<T*>* list);
	static float DistanceWithOutSquareRoot(D3DXVECTOR3 a, D3DXVECTOR3 b);
	float Distance(D3DXVECTOR3 a, D3DXVECTOR3 b) const;
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

inline float Utils::Distance(D3DXVECTOR3 a, D3DXVECTOR3 b) const
{
	return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
