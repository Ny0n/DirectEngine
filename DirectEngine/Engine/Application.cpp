#include "pch.h"

float Application::GetFrameRate(float fps)
{
	return fps <= 0.0f ? 0.0f : 1.0f / fps; // fps <= 0 means no limit
}

float Application::GetMaxStep(float maxStep)
{
	return maxStep <= _fixedTimestep ? _fixedTimestep : maxStep;
}

float Application::_targetFPS = APPLICATION_DEFAULT_FPS;
float Application::_targetFrameRate = GetFrameRate(_targetFPS);
float Application::_fixedTimestep = APPLICATION_DEFAULT_FIXED_TIMESTEP;
float Application::_maximumTimestep = GetMaxStep(APPLICATION_DEFAULT_MAXIMUM_TIMESTEP);
bool Application::_quit = false;
bool Application::_playing = false;
bool Application::_generatingScene = false;

// **************************** //

float Application::GetTargetFPS()
{
	return _targetFPS;
}

void Application::SetTargetFPS(float fps)
{
	_targetFPS = fps;
	_targetFrameRate = GetFrameRate(fps);
}

float Application::GetFixedTimestep()
{
	return _fixedTimestep;
}

void Application::SetFixedTimestep(float timestep)
{
	_fixedTimestep = timestep;
}

float Application::GetMaximumTimestep()
{
	return _maximumTimestep;
}

void Application::SetMaximumTimestep(float maxTimestep)
{
	_maximumTimestep = GetMaxStep(maxTimestep);
}

void Application::Quit()
{
	_quit = true;
}

bool Application::IsPlaying()
{
	return _playing;
}

bool Application::IsGeneratingScene()
{
	return _generatingScene;
}
