#include "pch.h"

Scene::Scene(IScene* scene) : _name(scene->GetName())
{
	Application::_generatingScene = true;
	_gameObjects = scene->GetContent();
	Application::_generatingScene = false;
}

Scene::~Scene()
{
	list<GameObject*> goCopy(_gameObjects); // safeguard

	for (auto go : goCopy) // we instantly destroy EVERYTHING
		Object::TryToDelete(go);

	goCopy.clear();

	_gameObjects.clear();

	// when deleting a scene, any new demand for destruction is irrelevant
	Execution::markedForDestruction.clear();
}

// **************************** //

bool Scene::IsEmpty() const
{
	return _gameObjects.empty();
}

// **************************** //

bool Scene::IsInScene(GameObject* go)
{
	return any_of(_gameObjects.begin(), _gameObjects.end(), [&](GameObject* sceneGo)
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
		_gameObjects.push_back(go);
		return true;
	}
	return false;
}

GameObject* Scene::RemoveFromScene(GameObject* go)
{
	if (!IsInScene(go))
		return nullptr;

	_gameObjects.remove(go);
	return go;
}
