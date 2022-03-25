﻿#pragma once

class Scene final
{
	friend class SceneManager;
	
	Scene(IScene* scene);

	bool IsEmpty() const;
	bool IsInScene(GameObject* go) const;
	
	bool AddToScene(GameObject* go);
	GameObject* RemoveFromScene(GameObject* go);

	const string name;
	list<GameObject*> gameObjects;

public:
	~Scene();

};
