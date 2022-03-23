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
	Utils::DeleteList(_scenes); // this also deletes _mainScene
	Utils::DeleteList(_protectedGameObjects);

	for (const auto scenes : _buildScenesS)
		delete(scenes.second);
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

	for (const auto element : _buildScenesI)
	{
		if (element.second->GetName() == _mainScene->name)
			return element.first;
	}
}

// **************************** //

void SceneManager::LoadScene(string sceneName)
{
	IScene* iscene = _buildScenesS[sceneName];
	if (iscene == nullptr)
	{
		Utils::Println("Scene \"" + sceneName + "\" doesn't exist!");
		return;
	}

	_sceneLoadChanges.push_back(sceneName);
}

void SceneManager::LoadScene(int buildIndex)
{
	IScene* iscene = _buildScenesI[buildIndex];
	if (iscene == nullptr)
	{
		Utils::Println("Scene with build number \"" + to_string(buildIndex) + "\" doesn't exist!");
		return;
	}

	_sceneLoadChanges.push_back(iscene->GetName());
}

void SceneManager::LoadSceneAdditive(string sceneName)
{
	IScene* iscene = _buildScenesS[sceneName];
	if (iscene == nullptr)
	{
		Utils::Println("Scene \"" + sceneName + "\" doesn't exist!");
		return;
	}

	_sceneAdditiveChanges.push_back(iscene->GetName());
}

void SceneManager::LoadSceneAdditive(int buildIndex)
{
	IScene* iscene = _buildScenesI[buildIndex];
	if (iscene == nullptr)
	{
		Utils::Println("Scene with build number \"" + to_string(buildIndex) + "\" doesn't exist!");
		return;
	}

	_sceneAdditiveChanges.push_back(iscene->GetName());
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

void SceneManager::ApplyLoadScene(string sceneName)
{
	Scene* sceneInstance = new Scene(_buildScenesS[sceneName]); // there we create a new fresh instance of the scene from the template

	if (HasScene()) // if we have scenes loaded, we need to unload them to load the new one
	{
		list<GameObject*> protectedGameObjects = {};

		for (Scene* scene : _scenes) // so for all of them, we save the _protectedGameObjects before deleting them, to add them to the new scene
		{
			if (!_protectedGameObjects.empty())
			{
				for (GameObject* go : scene->gameObjects)
				{
					if (Utils::Contains(&_protectedGameObjects, go))
					{
						protectedGameObjects.push_back(go);
						scene->RemoveFromScene(go);
					}
				}
			}
			delete(scene);
		}
		_scenes.clear();

		for (GameObject* go : protectedGameObjects)
			sceneInstance->AddToScene(go);
	}

	AddScene(sceneInstance);
}

void SceneManager::ApplyUnloadScene(string sceneName)
{
}

void SceneManager::ApplyAdditiveScene(string sceneName)
{
	AddScene(new Scene(_buildScenesS[sceneName]));
}
