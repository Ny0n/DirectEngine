#include "pch.h"

float GetFrameRate(float fps)
{
	return fps <= 0.0f ? 0.0f : 1.0f / fps; // fps <= 0 means no limit
}

float Application::targetFPS = APPLICATION_DEFAULT_FPS;
float Application::targetFrameRate = GetFrameRate(targetFPS);
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

void Application::Quit()
{
	quit = true;
}
