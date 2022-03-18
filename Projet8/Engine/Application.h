#pragma once

#define APPLICATION_DEFAULT_FPS 144

class Application final
{

private:
	static float _targetFPS;
	static float _targetFrameRate;

public:
	Application() = delete;

	static float GetTargetFPS();
	static void SetTargetFPS(float fps);

	static float GetTargetFrameRate();

};
