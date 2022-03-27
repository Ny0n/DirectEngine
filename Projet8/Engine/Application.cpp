#include "pch.h"

float Application::GetFrameRate(float fps)
{
	return fps <= 0.0f ? 0.0f : 1.0f / fps; // fps <= 0 means no limit
}

float Application::GetMaxStep(float maxStep)
{
	return maxStep <= fixedTimestep ? fixedTimestep : maxStep;
}

float Application::targetFPS = APPLICATION_DEFAULT_FPS;
float Application::targetFrameRate = GetFrameRate(targetFPS);
float Application::fixedTimestep = APPLICATION_DEFAULT_FIXED_TIMESTEP;
float Application::maximumTimestep = GetMaxStep(APPLICATION_DEFAULT_MAXIMUM_TIMESTEP);
bool Application::quit = false;
bool Application::playing = false;
bool Application::generatingScene = false;

// **************************** //

float Application::GetTargetFPS()
{
	return targetFPS;
}

void Application::SetTargetFPS(float fps)
{
	targetFPS = fps;
	targetFrameRate = GetFrameRate(fps);
}

float Application::GetFixedTimestep()
{
	return fixedTimestep;
}

void Application::SetFixedTimestep(float timestep)
{
	fixedTimestep = timestep;
}

float Application::GetMaximumTimestep()
{
	return maximumTimestep;
}

void Application::SetMaximumTimestep(float maxTimestep)
{
	maximumTimestep = GetMaxStep(maxTimestep);
}

void Application::Quit()
{
	quit = true;
}

bool Application::IsPlaying()
{
	return playing;
}

bool Application::IsGeneratingScene()
{
	return generatingScene;
}
