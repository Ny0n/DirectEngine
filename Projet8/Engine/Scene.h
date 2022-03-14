#pragma once

#include <list>

#include "GameObject.h"

class Scene
{

public:
	Scene();

	list<GameObject*> gameObjects;

	GameObject* CreateEmpty();
	bool Instantiate(GameObject* prefab);
	bool Destroy(GameObject* go);
	bool IsInScene(GameObject* go);

private:
	bool AddToScene(GameObject* go);
	bool RemoveFromScene(GameObject* go);

};
