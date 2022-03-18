#pragma once

#define APPLICATION_DEFAULT_FPS 144

class Application final
{

private:
	static float _targetFPS;
	static float _targetFrameRate;
	static bool _quit;

public:
	Application() = delete;

	static float GetTargetFPS();
	static void SetTargetFPS(float fps);

	static float GetTargetFrameRate();

	static void Quit();
	static bool GetQuit();

};
