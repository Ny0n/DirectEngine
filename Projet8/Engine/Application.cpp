#include "pch.h"

float GetFrameRate(float fps)
{
	return fps <= 0.0f ? 0.0f : 1.0f / fps; // fps <= 0 means no limit
}

float Application::targetFPS = APPLICATION_DEFAULT_FPS;
float Application::targetFrameRate = GetFrameRate(targetFPS);
float Application::fixedTimestep = APPLICATION_DEFAULT_FIXED_TIMESTEP;
bool Application::quit = false;

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

void Application::Quit()
{
	quit = true;
}
