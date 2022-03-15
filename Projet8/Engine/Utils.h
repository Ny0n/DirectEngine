#pragma once

class Utils
{

public:
	static void Println(string s);

	template<typename T>
	static bool Contains(list<T*>* list, T* value)
	{
		return (find(list->begin(), list->end(), value) != list->end());
	}

	template<typename T>
	static void DeleteList(list<T*>* list);
};

template <typename T>
void Utils::DeleteList(list<T*>* list)
{
	for (auto element : *list)
	{
		delete(element);
	}

	list->clear();
}

