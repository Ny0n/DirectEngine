#pragma once

class IScene
{

public:
	virtual ~IScene() = default;

	virtual string GetName() = 0;
	virtual void GenerateContent() = 0;

protected:
	GameObject* CreateEmpty();			// Shortcut to create a new empty GameObject

	void AddToScene(GameObject* go);	// Adds the given object (or prefab) to the scene

private:
	friend class Scene;

	list<GameObject*> GetContent();
	list<GameObject*> _gameObjects;		// since we are only using GetContent(), this never has any elements so there is no need for a destructor

};
