#pragma once

#define APPLICATION_DEFAULT_FPS 144
#define APPLICATION_DEFAULT_FIXED_TIMESTEP 0.02f

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
