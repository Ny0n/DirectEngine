#pragma once

class PhysicsEngine
{
    friend class Engine;
	friend class Execution;

	static void Clean();

	static void Update();

	static void CheckCollisions();

public:
	PhysicsEngine() = delete;

};
