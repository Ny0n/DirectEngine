#pragma once

#define APPLICATION_DEFAULT_FPS 144					// FPS, so 60 means 60 frames per second
#define APPLICATION_DEFAULT_FIXED_TIMESTEP 0.02f	// TIMESTEP, the time between each FixedUpdate, so 0.02f means 50 times per second

class Application final
{

public:
	Application() = delete;

	static float GetTargetFPS(); // The rate at which a new frame is run
	static void SetTargetFPS(float fps);

	static float GetFixedTimestep(); // The rate at which the FixedUpdate is called
	static void SetFixedTimestep(float timestep);

	static void Quit();

private:
	friend class Engine;

	static float targetFPS;
	static float targetFrameRate;
	static float fixedTimestep;
	static bool quit;

};
