#include "pch.h"

Profiler::Profiler() : displayCooldown(PROFILER_DISPLAY_COOLDOWN)
{
}

// *** Display *** //

string setSize(string str, int size) // this fills the given string with enough spaces to match the given size
{
	const int toAdd = size - static_cast<int>(str.size());
    for (int i = 0; i < toAdd; i++)
        str += " ";
    return str;
}

void Profiler::DisplayData()
{
    lastDisplayTime = Time::time;

    // for now, we just display a nice string with all of the data
    string s = setSize("frame: " + to_string(Time::frameCount), 15) + setSize("time: " + to_string(Time::time), 20) + " | " + setSize("FPS: " + to_string(Time::currentFps()), 18) + " | " + setSize("frameRate: " + to_string(Time::unscaledDeltaTime), 20) + setSize("frameTime: " + to_string(Time::frameTime()), 20) + setSize("startTime: " + to_string(startTime), 20) + setSize("updateTime: " + to_string(updateTime), 21) + setSize("presentTime: " + to_string(presentTime), 0) + " | " + setSize("fixedUpdateTime: " + to_string(fixedUpdateTime), 26);
    if (time1 != 0.0f)
        s += setSize("loop: " + to_string(loopCount), 15) + setSize("engineUpdate: " + to_string(engineUpdateTime), 20) + setSize("engineStart: " + to_string(engineStartTime), 20) + setSize("lateUpdate: " + to_string(lateUpdateTime), 20) + setSize("inputTime: " + to_string(inputTime), 20) + setSize("time1: " + to_string(time1), 15) + setSize("time2: " + to_string(time2), 15) + setSize("time3: " + to_string(time3), 15) + setSize("time4: " + to_string(time4), 15);

    Utils::Println(s);
}

// **************************** //

void Profiler::InitSystemTime()
{
    originalTime = timeGetTime() / 1000.0f;
    isPreciseTime = false;
    precisefrequency = 0.0f;

    LARGE_INTEGER frequency;
    memset(&frequency, 0, sizeof(LARGE_INTEGER));

    if (QueryPerformanceFrequency(&frequency) && frequency.QuadPart)
    {
        isPreciseTime = true;
        precisefrequency = (float)frequency.QuadPart;
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        originalPreciseTime = counter.QuadPart;
    }
}

float Profiler::GetSystemTime()
{
    // Precise
    if (isPreciseTime)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return (float)(counter.QuadPart - originalPreciseTime) / precisefrequency;
    }

    // Classic
    return (timeGetTime() / 1000.0f) - originalTime;
}

float Profiler::GetCurrentFPS()
{
    if (Time::unscaledDeltaTime <= 0.0f)
        return 100000;
    return 1.0f / Time::unscaledDeltaTime;
}

float Profiler::GetFrameTime()
{
    return frameTime;
}

/*void Profiler::AddFPS(float fpsIn)
{
    lastFps.push_back(fpsIn);
    int size = lastFps.size();
    if (size > 4000)
        lastFps.pop_front();

    float avg = 0.0f;
    for (const float fps : lastFps)
    {
        avg += fps;
    }
    avg = avg / size;

    currentFPS = avg;
}*/
