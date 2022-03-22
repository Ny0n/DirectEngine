#pragma once

class Component;
class Scene;

class Execution final
{
	friend class Engine;

	static void Clean();

	friend void EngineStart_(Component* component);
	static void EngineStart();
	friend void Start_(Component* component);
	static void Start();

	static void FixedUpdate();
	static void PhysicsUpdate();

	static void Input();
	static void Update();
	static void LateUpdate();
	static void EngineUpdate();
	
	static list<Component*> startedEngineComponents;
	static list<Component*> startedComponents;

public:
	Execution() = delete;

};
