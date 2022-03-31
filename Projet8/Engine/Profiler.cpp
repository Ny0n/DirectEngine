#include "pch.h"

Profiler::Profiler() : _displayCooldown(PROFILER_DISPLAY_COOLDOWN)
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
    _lastDisplayTime = Time::time;

    // for now, we just display a nice string with all of the data
    string s = setSize("frame: " + to_string(Time::frameCount), 15) + setSize("time: " + to_string(Time::time), 20) + " | " + setSize("FPS: " + to_string(Time::currentFps()), 18) + " | " + setSize("frameRate: " + to_string(Time::unscaledDeltaTime), 20) + setSize("frameTime: " + to_string(Time::frameTime()), 20) + setSize("startTime: " + to_string(_startTime), 20) + setSize("updateTime: " + to_string(_updateTime), 21) + setSize("presentTime: " + to_string(_presentTime), 0) + " | " + setSize("fixedUpdateTime: " + to_string(_fixedUpdateTime), 26);
    if (_time1 != 0.0f)
        s += setSize("loop: " + to_string(_loopCount), 15) + setSize("engineUpdate: " + to_string(_engineUpdateTime), 20) + setSize("engineStart: " + to_string(_engineStartTime), 20) + setSize("lateUpdate: " + to_string(_lateUpdateTime), 20) + setSize("inputTime: " + to_string(_inputTime), 20) + setSize("time1: " + to_string(_time1), 15) + setSize("time2: " + to_string(_time2), 15) + setSize("time3: " + to_string(_time3), 15) + setSize("time4: " + to_string(_time4), 15);

    Utils::Println(s);
}

// **************************** //

void Profiler::InitSystemTime()
{
    _originalTime = timeGetTime() / 1000.0f;
    _isPreciseTime = false;
    _precisefrequency = 0.0f;

    LARGE_INTEGER frequency;
    memset(&frequency, 0, sizeof(LARGE_INTEGER));

    if (QueryPerformanceFrequency(&frequency) && frequency.QuadPart)
    {
        _isPreciseTime = true;
        _precisefrequency = static_cast<float>(frequency.QuadPart);
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        _originalPreciseTime = counter.QuadPart;
    }
}

float Profiler::GetSystemTime()
{
    // Precise
    if (_isPreciseTime)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return static_cast<float>(counter.QuadPart - _originalPreciseTime) / _precisefrequency;
    }

    // Classic
    return (timeGetTime() / 1000.0f) - _originalTime;
}

float Profiler::GetCurrentFPS()
{
    if (Time::unscaledDeltaTime <= 0.0f)
        return 100000;
    return 1.0f / Time::unscaledDeltaTime;
}

float Profiler::GetFrameTime()
{
    return _frameTime;
}