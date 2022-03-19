#pragma once

#define APPLICATION_DEFAULT_FPS 144

class Application final
{

public:
	Application() = delete;

	static float GetTargetFPS();
	static void SetTargetFPS(float fps);

	static void Quit();

private:
	friend class Engine;

	static float targetFPS;
	static float targetFrameRate;
	static bool quit;

};
