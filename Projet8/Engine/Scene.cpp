#include "pch.h"

Scene::Scene(IScene* scene) : name(scene->GetName()), gameObjects(scene->GetContent())
{
}

Scene::~Scene()
{
	list<GameObject*> goCopy(gameObjects);
	for (auto element : goCopy)
		delete(element);

	goCopy.clear();
	gameObjects.clear();
}

// **************************** //

bool Scene::IsEmpty() const
{
	return gameObjects.empty();
}

// **************************** //

bool Scene::IsInScene(GameObject* go) const
{
	for (GameObject* sceneGo : gameObjects)
	{
		if (sceneGo == go) // TODO add ID to gameobjects?
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
