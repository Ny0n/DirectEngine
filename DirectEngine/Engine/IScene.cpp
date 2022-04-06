#include "pch.h"

GameObject* IScene::CreateEmpty()
{
	return new GameObject();
}

// **************************** //

void IScene::AddToScene(GameObject* go)
{
	_gameObjects.push_back(go);
}

list<GameObject*> IScene::GetContent()
{
	_gameObjects.clear();

	GenerateContent();
	list<GameObject*> copy(_gameObjects);

	_gameObjects.clear();

	return copy;
}
