#pragma once

#define APPLICATION_DEFAULT_FPS 144

class Application final
{

private:
	static float _targetFPS;
	static float _targetFrameRate;

public:
	Application() = delete;

	static float GetTargetFPS() { return _targetFPS; }
	static void SetTargetFPS(float fps)
	{
		_targetFPS = fps;
		_targetFrameRate = fps < 0.0f ? 0.0f : 1.0f / fps; // fps < 0 means no limit
	}

	static float GetTargetFrameRate() { return _targetFrameRate; }

};

float Application::_targetFPS = APPLICATION_DEFAULT_FPS;
float Application::_targetFrameRate = _targetFPS < 0.0f ? 0.0f: 1.0f / _targetFPS;
