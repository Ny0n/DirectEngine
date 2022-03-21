#pragma once

#define APPLICATION_DEFAULT_FPS 1					// FPS, so 60 means 60 frames per second
#define APPLICATION_DEFAULT_FIXED_TIMESTEP 0.02f	// TIMESTEP, the time between each FixedUpdate, so 0.02f means 50 times per second
#define APPLICATION_DEFAULT_MAXIMUM_TIMESTEP 0.33f	// MAXIMUM TIMESTEP, it's complicated, but basically it's the maximum delay the fixed update is allowed to catch up in case of frame drops, CANNOT be less than the timestep

class Application final
{

public:
	Application() = delete;

	static float GetTargetFPS(); // The rate at which a new frame is run
	static void SetTargetFPS(float fps);

	static float GetFixedTimestep(); // The rate at which the FixedUpdate is called
	static void SetFixedTimestep(float timestep);
	static float GetMaximumTimestep(); // The rate at which the FixedUpdate is called
	static void SetMaximumTimestep(float maxTimestep);

	static void Quit();

private:
	friend class Engine;

	// utils funcs
	static float GetFrameRate(float fps);
	static float GetMaxStep(float maxStep);

	static float targetFPS;
	static float targetFrameRate;
	static float fixedTimestep;
	static float maximumTimestep;
	static bool quit;

};
