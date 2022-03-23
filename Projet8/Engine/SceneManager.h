#pragma once

class SceneManager final
{

public:
	static bool AddToBuild(IScene* scene); // only works while the app is not running
	static bool HasScenesInBuild();
	static int BuildScenesCount();

	static bool HasScene();
	static int ActiveSceneCount();

	static bool Instantiate(GameObject* go);
	static GameObject* Remove(GameObject* go);

	static list<string> GetActiveScenes();
	static string GetActiveSceneName();
	static int GetActiveSceneIndex();

	static bool SetActiveScene(string sceneName);
	static bool SetActiveScene(int buildIndex);

	static void LoadScene(string sceneName);
	static void LoadScene(int buildIndex);
	static void UnloadScene(string sceneName);
	static void UnloadScene(int buildIndex);
	static void LoadSceneAdditive(string sceneName); // additive, there can be multiple scenes active at the same time (but no duplicate scenes)
	static void LoadSceneAdditive(int buildIndex);

	static bool IsEmpty(); // returns true if every scene is empty
	static void DontDestroyOnLoad(GameObject* go);
	static list<GameObject*> GetAllGameObjects();

	static void ForEachGameObject(const function<void(GameObject*)>& consumer);
	static void ForEachComponent(const function<void(Component*)>& consumer);

	static void Clean();

private:
	friend class Execution;

	// the engine accesses these two functions and does the scene change at the end of the frame
	static bool ChangeRequired();
	static void ApplyChanges();

	static void ApplyLoadScene(string sceneName);
	static list<string> _sceneLoadChanges;
	static void ApplyUnloadScene(string sceneName);
	static list<string> _sceneUnoadChanges;
	static void ApplyAdditiveScene(string sceneName);
	static list<string> _sceneAdditiveChanges;

	static void ForEachScene(const function<void(Scene*)>& consumer);

	// helpers
	static void SaveProtectedObjects(Scene* scene, list<GameObject*>& list);
	static void AddScene(Scene* scene);
	static bool SetMainScene(string sceneName);
	static IScene* FindScene(string sceneName);
	static IScene* FindScene(int buildIndex);

	static map<string, IScene*> _buildScenesS;
	static map<int, IScene*> _buildScenesI;

	static Scene* _mainScene;
	static list<Scene*> _scenes;

	static list<GameObject*> _protectedGameObjects;

};
