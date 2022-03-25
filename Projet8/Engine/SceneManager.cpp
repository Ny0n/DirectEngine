#include "pch.h"

Scene* SceneManager::_mainScene = nullptr;
list<Scene*> SceneManager::_scenes = {};
list<GameObject*> SceneManager::_protectedGameObjects = {};
map<string, IScene*> SceneManager::_buildScenesS = {};
map<int, IScene*> SceneManager::_buildScenesI = {};
list<string> SceneManager::_sceneLoadChanges = {};
list<string> SceneManager::_sceneUnoadChanges = {};
list<string> SceneManager::_sceneAdditiveChanges = {};

bool SceneManager::AddToBuild(IScene* scene)
{
	if (Application::IsPlaying())
	{
		Utils::Println("Cannot add a new scene to build settings while the application is running!");
		return false;
	}

	if (_buildScenesS.count(scene->GetName()) == 0)
	{
		_buildScenesS[scene->GetName()] = scene;
		_buildScenesI[static_cast<int>(_buildScenesS.size())] = scene;
		return true;
	}
	else
	{
		Utils::Println("Scene \"" + scene->GetName() + "\" already added to build settings!");
		return false;
	}
}

bool SceneManager::HasScenesInBuild()
{
	return !_buildScenesS.empty();
}

int SceneManager::BuildScenesCount()
{
	return static_cast<int>(_buildScenesS.size());
}

// **************************** //

void SceneManager::Clean()
{
	Utils::DeleteList(_scenes); // this also deletes _mainScene, and recursively, everything inside _protectedGameObjects
	_scenes.clear();
	_protectedGameObjects.clear();

	Utils::DeleteMapSecond(_buildScenesS); // since the IScene* are the same in both maps, we only need to delete them one one map to delete them in both
	_buildScenesS.clear();
	_buildScenesI.clear();
}

bool SceneManager::HasScene()
{
    return _mainScene != nullptr;
}

int SceneManager::ActiveSceneCount()
{
	return static_cast<int>(_scenes.size());
}

// **************************** //

// Adds the given gameobject to the loaded scene
bool SceneManager::Instantiate(GameObject* go)
{
	if (HasScene())
		return _mainScene->AddToScene(go);
	return false;
}

// Returns the removed gameobject if it has been found in the loaded scened
GameObject* SceneManager::Remove(GameObject* go)
{
	for (Scene* scene : _scenes)
	{
		if (scene->RemoveFromScene(go) != nullptr)
			return go;
	}
	return nullptr;
}

list<string> SceneManager::GetActiveSceneNames()
{
	list<string> names = {};

	for (Scene* scene : _scenes)
		names.push_back(scene->name);

	return names;
}

list<int> SceneManager::GetActiveSceneIndexes()
{
	list<int> indexes = {};

	for (Scene* scene : _scenes)
		indexes.push_back(FindSceneIndex(scene->name));

	return indexes;
}

// **************************** //

string SceneManager::GetActiveSceneName()
{
	if (!HasScene())
		return "";

	return _mainScene->name;
}

int SceneManager::GetActiveSceneIndex()
{
	if (!HasScene())
		return 0;

	return FindSceneIndex(_mainScene->name);
}

bool SceneManager::SetActiveScene(string sceneName)
{
	IScene* iscene = FindScene(sceneName);
	if (iscene != nullptr)
		return SetMainScene(iscene->GetName());
	return false;
}

bool SceneManager::SetActiveScene(int buildIndex)
{
	IScene* iscene = FindScene(buildIndex);
	if (iscene != nullptr)
		return SetMainScene(iscene->GetName());
	return false;
}

// **************************** //

void SceneManager::LoadScene(string sceneName)
{
	IScene* iscene = FindScene(sceneName);
	if (iscene != nullptr)
		_sceneLoadChanges.push_back(iscene->GetName());
}

void SceneManager::LoadScene(int buildIndex)
{
	IScene* iscene = FindScene(buildIndex);
	if (iscene != nullptr)
		_sceneLoadChanges.push_back(iscene->GetName());
}

void SceneManager::UnloadScene(string sceneName)
{
	IScene* iscene = FindScene(sceneName);
	if (iscene != nullptr)
		_sceneUnoadChanges.push_back(iscene->GetName());
}

void SceneManager::UnloadScene(int buildIndex)
{
	IScene* iscene = FindScene(buildIndex);
	if (iscene != nullptr)
		_sceneUnoadChanges.push_back(iscene->GetName());
}

void SceneManager::LoadSceneAdditive(string sceneName)
{
	IScene* iscene = FindScene(sceneName);
	if (iscene != nullptr)
	{
		for (const Scene* scene : _scenes)
		{
			if (scene->name == iscene->GetName())
			{
				Utils::Println("ERROR: (LoadSceneAdditive) Scene \"" + iscene->GetName() + "\" is already loaded!");
				return;
			}
		}
		_sceneAdditiveChanges.push_back(iscene->GetName());
	}
}

void SceneManager::LoadSceneAdditive(int buildIndex)
{
	IScene* iscene = FindScene(buildIndex);
	if (iscene != nullptr)
	{
		for (const Scene* scene : _scenes)
		{
			if (scene->name == iscene->GetName())
			{
				Utils::Println("ERROR: (LoadSceneAdditive) Scene \"" + iscene->GetName() + "\" is already loaded!");
				return;
			}
		}
		_sceneAdditiveChanges.push_back(iscene->GetName());
	}
}

// **************************** //

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

	ForEachGameObject([&](GameObject* go) mutable
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

bool SceneManager::SetMainScene(string sceneName)
{
	for (Scene* scene : _scenes)
	{
		if (scene->name == sceneName)
		{
			_mainScene = scene;
			return true;
		}
	}

	Utils::Println("ERROR: (SetActiveScene) Scene \"" + sceneName + "\" not found in currently loaded scenes.");
	return false;
}

int SceneManager::FindSceneIndex(string sceneName)
{
	for (const auto element : _buildScenesI)
	{
		if (element.second->GetName() == sceneName)
			return element.first;
	}
	return 0;
}

IScene* SceneManager::FindScene(string sceneName)
{
	IScene* iscene = _buildScenesS[sceneName];
	if (iscene == nullptr)
	{
		Utils::Println("ERROR: (FindScene) Scene \"" + sceneName + "\" doesn't exist!");
		return nullptr;
	}
	return iscene;
}

IScene* SceneManager::FindScene(int buildIndex)
{
	IScene* iscene = _buildScenesI[buildIndex];
	if (iscene == nullptr)
	{
		Utils::Println("ERROR: (FindScene) Scene with build number \"" + to_string(buildIndex) + "\" doesn't exist!");
		return nullptr;
	}
	return iscene;
}

// **************************** //

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

// **************************** //

bool SceneManager::ChangeRequired()
{
	return !_sceneLoadChanges.empty()
		|| !_sceneUnoadChanges.empty()
		|| !_sceneAdditiveChanges.empty();
}

void SceneManager::ApplyChanges()
{
	if (!_sceneLoadChanges.empty())
	{
		ApplyLoadScene(*_sceneLoadChanges.begin()); // we only load the first scene that was asked to be to loaded
	}
	else if (!_sceneUnoadChanges.empty())
	{
		for (const auto name : _sceneUnoadChanges)
		{
			ApplyUnloadScene(name);
		}
	}

	if (!_sceneAdditiveChanges.empty())
	{
		for (const auto name : _sceneAdditiveChanges)
		{
			ApplyAdditiveScene(name);
		}
	}

	_sceneLoadChanges.clear();
	_sceneUnoadChanges.clear();
	_sceneAdditiveChanges.clear();
}

// adds every protected object found in the scene to the given list
void SceneManager::SaveProtectedObjects(Scene* sceneIn, list<GameObject*>& listIn)
{
	list<GameObject*> toRemove = {};

	for (GameObject* go : sceneIn->gameObjects)
	{
		if (Utils::Contains(&_protectedGameObjects, go))
		{
			listIn.push_back(go);
			toRemove.push_back(go);
		}
	}

	for (GameObject* go : toRemove)
		sceneIn->RemoveFromScene(go);
}

void SceneManager::ApplyLoadScene(string sceneName)
{
	Scene* loadScene = new Scene(_buildScenesS[sceneName]); // there we create a new fresh instance of the scene from the template

	if (HasScene()) // if we have scenes loaded, we need to unload them to load the new one (so pretty much every time but the first load)
	{
		// we save all the protected game objects found in the active scenes
		list<GameObject*> protectedGameObjects = {};

		for (Scene* scene : _scenes)
		{
			if (!_protectedGameObjects.empty())
				SaveProtectedObjects(scene, protectedGameObjects);
		}

		for (GameObject* go : protectedGameObjects)
			loadScene->AddToScene(go);

		// and then we can unload all of the active scenes
		for (Scene* scene : _scenes)
			delete(scene);
		_scenes.clear();
	}

	AddScene(loadScene);
}

void SceneManager::ApplyUnloadScene(string sceneName)
{
	if (_scenes.size() <= 1)
	{
		Utils::Println("ERROR: (UnloadScene) Cannot unload a scene if it is the only one active.");
		return;
	}
	
	for (Scene* scene : _scenes)
	{
		if (scene->name == sceneName) // we found the scene to unload (remove)
		{
			if (GetActiveSceneName() == sceneName) // if the current main scene is the one we're about to remove, we need to find a new scene to make the main scene
			{
				const Scene* switchScene = nullptr;

				for (Scene* scene : _scenes)
				{
					if (scene->name != sceneName) // we found a scene to switch to
					{
						switchScene = scene;
						break;
					}
				}

				// we switch the main scene
				SetMainScene(switchScene->name); // switchScene should never be null
			}

			// we save the protected game objects in the scene we're about to unload
			list<GameObject*> protectedGameObjects = {};

			if (!_protectedGameObjects.empty())
				SaveProtectedObjects(scene, protectedGameObjects);

			for (GameObject* go : protectedGameObjects)
				_mainScene->AddToScene(go);

			// we unload the scene
			_scenes.remove(scene);
			delete(scene);

			return;
		}
	}

	Utils::Println("ERROR: (UnloadScene) The scene wasn't loaded.");
}

void SceneManager::ApplyAdditiveScene(string sceneName)
{
	AddScene(new Scene(_buildScenesS[sceneName]));
}
