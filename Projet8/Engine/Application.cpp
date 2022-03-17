#include "pch.h"

#include "Application.h"

float Application::_targetFPS = APPLICATION_DEFAULT_FPS;
float Application::_targetFrameRate = _targetFPS <= 0.0f ? 0.0f : 1.0f / _targetFPS;

float Application::GetTargetFPS()
{
	return _targetFPS;
}

void Application::SetTargetFPS(float fps)
{
	_targetFPS = fps;
	_targetFrameRate = fps <= 0.0f ? 0.0f : 1.0f / fps; // fps <= 0 means no limit
}

float Application::GetTargetFrameRate()
{
	return _targetFrameRate;
}
