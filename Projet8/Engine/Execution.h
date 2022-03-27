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

	// this is only for optimization
	friend class Scene;
	friend class Object;
	friend class GameObject;
	friend class Component;
	static list<Object*> markedForInstantiation;
	static list<Object*> markedForDestruction;

public:
	Execution() = delete;

};
