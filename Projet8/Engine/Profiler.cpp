#include "pch.h"

string setSize(string str, int size) // this fills the given string with enough spaces to match the given size
{
	const int toAdd = size - static_cast<int>(str.size());
    for (int i = 0; i < toAdd; i++)
        str += " ";
    return str;
}

void Profiler::DisplayData()
{
    // for now, we just display a nice string with all of the data
    string s = setSize("frame: " + to_string(currentFrame), 15) + " | " + setSize("runTime: " + to_string(runTime), 20) + setSize("FPS: " + to_string(currentFPS), 18) + setSize("frameRate: " + to_string(currentFrameRate), 20) + " | " + setSize("frameTime: " + to_string(frameTime), 20) + setSize("startTime: " + to_string(startTime), 20) + setSize("updateTime: " + to_string(updateTime), 21) + setSize("presentTime: " + to_string(presentTime), 0);
    if (time1 != 0.0f)
        s += setSize("time1: " + to_string(time1), 15) + setSize("time2: " + to_string(time2), 15) + setSize("time3: " + to_string(time3), 15) + setSize("time4: " + to_string(time4), 15);

    Utils::Println(s);
}

// **************************** //

void Profiler::TryDisplayData()
{
    _displayCooldown -= currentFrameRate;
    if (_displayCooldown <= 0.0f)
    {
        _displayCooldown = PROFILER_DISPLAY_COOLDOWN;
        DisplayData();
    }
}

void Profiler::InitSystemTime()
{
    _startTime = timeGetTime() / 1000.0f;
    _isPreciseTime = false;
    _frequency = 0.0f;

    LARGE_INTEGER frequency;
    memset(&frequency, 0, sizeof(LARGE_INTEGER));

    if (QueryPerformanceFrequency(&frequency) && frequency.QuadPart)
    {
        _isPreciseTime = true;
        _frequency = (float)frequency.QuadPart;
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        _startPreciseTime = counter.QuadPart;
    }
}

float Profiler::GetSystemTime()
{
    // Precise
    if (_isPreciseTime)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return (float)(counter.QuadPart - _startPreciseTime) / _frequency;
    }

    // Classic
    return (timeGetTime() / 1000.0f) - _startTime;
}
