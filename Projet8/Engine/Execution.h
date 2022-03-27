#pragma once

class Object;
class GameObject;
class Component;

class Execution final
{
	friend class Engine;

	static void Clean();
	
	static void EngineStart();
	static void Start();

	static void FixedUpdate();
	static void PhysicsUpdate();

	static void Input();
	static void Update();
	static void LateUpdate();
	static void EngineUpdate();

	static void CheckForSceneUpdate();

	friend class Scene;
	friend class Object;
	friend class GameObject;
	static list<GameObject*> goMarkedForInstantiation;
	static list<GameObject*> goMarkedForDestruction;
	friend class Component;
	static list<Component*> compMarkedForInstantiation;
	static list<Component*> compMarkedForDestruction;

public:
	Execution() = delete;

};
