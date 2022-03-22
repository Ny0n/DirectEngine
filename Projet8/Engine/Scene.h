#pragma once

class GameObject;

class Scene
{

public:
	Scene() = default;
	virtual ~Scene();

	list<GameObject*> gameObjects;

	static GameObject* CreateEmpty();

	bool Instantiate(GameObject* prefab);
	GameObject* Remove(GameObject* go);

	bool IsEmpty() const;
	bool IsInScene(GameObject* go) const;

private:
	bool AddToScene(GameObject* go);
	GameObject* RemoveFromScene(GameObject* go);

};
