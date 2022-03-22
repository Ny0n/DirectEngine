#include "pch.h"

Scene::~Scene()
{
	Utils::DeleteList(&gameObjects);
}

GameObject* Scene::CreateEmpty()
{
	return new GameObject();
}

// **************************** //

bool Scene::Instantiate(GameObject* prefab)
{
	return AddToScene(prefab);
}

GameObject* Scene::Remove(GameObject* go)
{
	return RemoveFromScene(go);
}

bool Scene::IsEmpty() const
{
	return gameObjects.empty();
}

// **************************** //

bool Scene::IsInScene(GameObject* go) const
{
	for (GameObject* sceneGo : gameObjects)
	{
		if (sceneGo == go) // TODO add ID to gameobjects
			return true;
	}
	return false;
}

bool Scene::AddToScene(GameObject* go)
{
	if (!IsInScene(go))
	{
		gameObjects.push_back(go);
		return true;
	}
	return false;
}

GameObject* Scene::RemoveFromScene(GameObject* go)
{
	if (!IsInScene(go))
		return nullptr;

	gameObjects.remove(go);
	return go;
}
