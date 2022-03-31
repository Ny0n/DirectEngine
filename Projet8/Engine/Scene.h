#pragma once

class Scene final
{
	friend class SceneManager;
	
	Scene(IScene* scene);

	bool IsEmpty() const;
	bool IsInScene(GameObject* go);
	
	bool AddToScene(GameObject* go);
	GameObject* RemoveFromScene(GameObject* go);

	const string _name;
	list<GameObject*> _gameObjects;

public:
	~Scene();

};
