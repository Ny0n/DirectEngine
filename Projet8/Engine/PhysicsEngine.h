#pragma once

class Collider;

class PhysicsEngine
{
    friend class Engine;
	friend class Execution;

	static void Clean();

	static void Update();

	static void CheckCollisions();

    static void ExecuteTrigger(Collider* collider, Collider* collideWith);
    static void EndTrigger(Collider* collider, Collider* collideWith);

public:
	PhysicsEngine() = delete;

};
