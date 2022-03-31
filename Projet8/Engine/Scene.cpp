#include "pch.h"

Scene::Scene(IScene* scene) : name(scene->GetName())
{
	Application::_generatingScene = true;
	gameObjects = scene->GetContent();
	Application::_generatingScene = false;
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

bool Scene::IsInScene(GameObject* go)
{
	return any_of(gameObjects.begin(), gameObjects.end(), [&](GameObject* sceneGo)
	{
		return sceneGo == go;
	});

	// other way of doing the same thing: (but rider says that using any_of is better)
	// for (GameObject* sceneGo : gameObjects)
	// {
	// 	if (sceneGo == go)
	// 		return true;
	// }
	// return false;
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
