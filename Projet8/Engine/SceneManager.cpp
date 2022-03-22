#include "pch.h"

Scene* SceneManager::_mainScene = nullptr;
list<Scene*> SceneManager::_scenes = {};
list<GameObject*> SceneManager::_protectedGameObjects = {};

void SceneManager::Clean()
{
	Utils::DeleteList(&_scenes); // this also deletes _mainScene
	Utils::DeleteList(&_protectedGameObjects);
}

bool SceneManager::HasScene()
{
    return _mainScene != nullptr;
}

int SceneManager::SceneCount()
{
	return static_cast<int>(_scenes.size());
}

// **************************** //

// Adds the given gameobject to the loaded scene
bool SceneManager::Instantiate(GameObject* go)
{
	if (HasScene())
		return _mainScene->Instantiate(go);
	return false;
}

// Returns the removed gameobject if it has been found in the loaded scened
GameObject* SceneManager::Remove(GameObject* go)
{
	for (Scene* scene : _scenes)
	{
		if (scene->Remove(go) != nullptr)
			return go;
	}
	return nullptr;
}

// **************************** //

void SceneManager::LoadScene(Scene* sceneIn)
{
	// TODO must notify engine and do it at the end of the frame!

	if (HasScene()) // if we have scenes loaded, we need to unload them to load the new one
	{
		list<GameObject*> protectedGameObjects = {};

		for (Scene* scene : _scenes) // so for all of them, we save the _protectedGameObjects before deleting them, to add them to the new scene
		{
			for (GameObject* go : scene->gameObjects)
			{
				if (Utils::Contains(&_protectedGameObjects, go))
				{
					protectedGameObjects.push_back(go);
					scene->Remove(go);
				}
			}
			delete(scene);
		}
			
		_scenes.clear();

		for (GameObject* go : protectedGameObjects)
			sceneIn->Instantiate(go);
	}

	AddScene(sceneIn);
}

void SceneManager::LoadSceneAdditive(Scene* sceneIn)
{
	AddScene(sceneIn);
}

void SceneManager::DontDestroyOnLoad(GameObject* go)
{
	if (!Utils::Contains(&_protectedGameObjects, go))
	{
		_protectedGameObjects.push_back(go);
	}
}

bool SceneManager::IsEmpty()
{
	for (const Scene* scene : _scenes)
	{
		if (!scene->IsEmpty())
			return false;
	}
	return true;
}

list<GameObject*> SceneManager::GetAllGameObjects()
{
	list<GameObject*> gos = {};

	ForEachGameObject([=](GameObject* go) mutable
	{
		gos.push_back(go);
	});

	return gos;
}

// **************************** //

void SceneManager::AddScene(Scene* scene)
{
	if (_scenes.empty())
		_mainScene = scene;
	_scenes.push_back(scene);
}

void SceneManager::ForEachScene(const function<void(Scene*)>& consumer)
{
	for (Scene* scene : _scenes)
	{
		consumer(scene);
	}
}

void SceneManager::ForEachGameObject(const function<void(GameObject*)>& consumer)
{
	auto forAllScenes = [=](const Scene* scene)
	{
		for (GameObject* go : scene->gameObjects)
		{
			consumer(go);
		}
	};

	ForEachScene(forAllScenes);
}

void SceneManager::ForEachComponent(const function<void(Component*)>& consumer)
{
	auto forAllGameObjects = [=](const GameObject* go)
	{
		for (Component* component : go->components)
		{
			consumer(component);
		}
	};

	ForEachGameObject(forAllGameObjects);
}
