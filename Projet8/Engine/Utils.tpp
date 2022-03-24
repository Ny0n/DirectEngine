#pragma once

template <typename T>
bool Utils::Contains(list<T*>* list, T* value)
{
	return (find(list->begin(), list->end(), value) != list->end());
}

template <typename T>
bool Utils::Contains(list<T>* list, T value)
{
	return (find(list->begin(), list->end(), value) != list->end());
}

template <typename T>
void Utils::DeleteList(list<T*> listIn)
{
	for (auto element : listIn)
	{
		delete(element);
	}
	listIn.clear();
}

template <typename K, typename V>
void Utils::DeleteMap(map<K*, V*> mapIn)
{
	for (auto element : mapIn)
	{
		delete(element.first);
		delete(element.second);
	}
	mapIn.clear();
}

template <typename K, typename V>
void Utils::DeleteMapFirst(map<K*, V> mapIn)
{
	for (auto element : mapIn)
	{
		delete(element.first);
	}
	mapIn.clear();
}

template <typename K, typename V>
void Utils::DeleteMapSecond(map<K, V*> mapIn)
{
	for (auto element : mapIn)
	{
		delete(element.second);
	}
	mapIn.clear();
}
