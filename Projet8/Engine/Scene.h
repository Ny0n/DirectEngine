#pragma once

class GameObject;

class Scene
{

public:
	Scene() = default;
	virtual ~Scene() = default;

	list<GameObject*> gameObjects;

	static GameObject* CreateEmpty();
	bool Instantiate(GameObject* prefab);
	bool Destroy(GameObject* go);
	bool IsInScene(GameObject* go) const;

private:
	bool AddToScene(GameObject* go);
	bool RemoveFromScene(GameObject* go);

};
