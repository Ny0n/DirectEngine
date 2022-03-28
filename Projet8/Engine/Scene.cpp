﻿#include "pch.h"

Scene::Scene(IScene* scene) : name(scene->GetName())
{
	Application::generatingScene = true;
	gameObjects = scene->GetContent();
	Application::generatingScene = false;
}

Scene::~Scene()
{
	list<GameObject*> goCopy(gameObjects); // safeguard

	for (auto go : goCopy) // we instantly destroy EVERYTHING
		Object::TryToDelete(go);

	goCopy.clear();

	gameObjects.clear();

	// when deleting a scene, any new demand for destruction is irrelevant
	Execution::markedForDestruction.clear();
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
