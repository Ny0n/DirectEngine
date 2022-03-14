#include "pch.h"

#include "Profiler.h"

#include "Utils.h"

Profiler::Profiler()
{
    InitSystemTime();
}

void Profiler::DisplayData()
{
    stringstream ss;
    ss << "runTime: " << to_string(runTime) << " FPS: " << to_string(currentFPS) << " frameRate: " << to_string(currentFrameRate) << " frameTime: " << to_string(frameTime) << " startTime: " << to_string(startTime) << " updateTime: " << to_string(updateTime);
    string s = ss.str();
    Utils::Println(s);
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
