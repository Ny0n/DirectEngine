#include "pch.h"

#include "Scene.h"

#include "Utils.h"


GameObject* Scene::CreateEmpty()
{
	return new GameObject();
}

// **************************** //

bool Scene::Instantiate(GameObject* prefab)
{
	return AddToScene(prefab);
}

bool Scene::Destroy(GameObject* go)
{
	if (RemoveFromScene(go))
	{
		delete(go);
		return true;
	}
	return false;
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

bool Scene::RemoveFromScene(GameObject* go)
{
	if (!IsInScene(go))
	{
		return false;
	}
	gameObjects.remove(go);
	return true;
}
