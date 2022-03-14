#pragma once

#include <timeapi.h>
#include <profileapi.h>
#include <string.h>
#include <sstream>

#include "Utils.h"

using namespace std;

class Profiler {

private:
    template<typename T, typename... Args>
    auto timed(float& timeVar, T& func, Args&... args);

    void initSystemTime();

    float _startTime;
    bool _isPreciseTime;
    float _frequency;
    LONGLONG _startPreciseTime;

public:
    Profiler() { initSystemTime(); }

    float getSystemTime();
    void displayData();

    template<typename T, typename... Args>
    void* timedRunner(float& timeVar, const T& func, Args&... args);

    template<typename T, typename... Args>
    auto timedSupplier(float& timeVar, const T& func, Args&... args);

    // *** Profiler Data *** //

    float runTime;

    float currentFPS;
    float currentFrameRate;

    float startTime;
    float newFrameTime;

};

// **************************** //

void Profiler::displayData()
{
    stringstream ss;
    ss << "startTime: " << to_string(startTime) << " runTime: " << to_string(runTime) << " FPS: " << to_string(currentFPS) << " frameRate: " << to_string(currentFrameRate) << " update: " << to_string(newFrameTime);
    string s = ss.str();
    Utils::Println(s);
}

void Profiler::initSystemTime()
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

float Profiler::getSystemTime()
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

// **************************** //

template<typename T, typename... Args>
auto Profiler::timed(float& timeVar, T& func, Args&... args) {
    float start = getSystemTime();
    // --------------------------------------

    auto result = func(args...); // we run the given function

    // --------------------------------------
    float end = getSystemTime();

    float elapsed = end - start;

    timeVar = elapsed;

    return result;
}

// **************************** //

template<typename T, typename... Args>
void* Profiler::timedRunner(float& timeVar, const T& func, Args&... args) {
    // since returning void is causing problems, i'm transferring the func to an other one that returns void* through a lambda
    // (it's one way to do it)
    auto voidFunc = [=](Args&... args)
    {
        func(args...);
        return nullptr;
    };

    return timed(timeVar, voidFunc, args...);
}

template<typename T, typename... Args>
auto Profiler::timedSupplier(float& timeVar, const T& func, Args&... args) {
    return timed(timeVar, func, args...);
}
