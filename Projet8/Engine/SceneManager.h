#pragma once

class SceneManager final
{

public:
	static bool HasScene();
	static int SceneCount();

	static bool Instantiate(GameObject* go);
	static GameObject* Remove(GameObject* go);

	static void LoadScene(Scene* sceneIn);
	static void LoadSceneAdditive(Scene* sceneIn); // additive, there can be multiple scenes active at the same time

	static void DontDestroyOnLoad(GameObject* go);

	static bool IsEmpty(); // returns true if every scene is empty
	static list<GameObject*> GetAllGameObjects();

	static void ForEachGameObject(const function<void(GameObject*)>& consumer);
	static void ForEachComponent(const function<void(Component*)>& consumer);

	static void Clean();

private:
	static void ForEachScene(const function<void(Scene*)>& consumer);

	static void AddScene(Scene* scene);

	static Scene* _mainScene;
	static list<Scene*> _scenes;

	static list<GameObject*> _protectedGameObjects;

};
