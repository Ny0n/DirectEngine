﻿#pragma once

class Profiler {

private:
    template<typename T, typename... Args>
    auto Timed(float& timeVar, const T& func, Args&... args);

    void InitSystemTime();

    float _startTime{};
    bool _isPreciseTime{};
    float _frequency{};
    LONGLONG _startPreciseTime{};

public:
    Profiler();

    float GetSystemTime();
    void DisplayData();

    template<typename T, typename... Args>
    void* TimedRunner(float& timeVar, const T& func, Args&... args);

    template<typename T, typename... Args>
    auto TimedSupplier(float& timeVar, const T& func, Args&... args);

    // *** Profiler Data *** //

    /*void addFPS(float fpsIn)
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

    float runTime{};

    float currentFPS{};
    float currentFrameRate{};

    float frameTime{};
    float startTime{};
    float updateTime{};
    float presentTime{};

    float time1{};
    float time2{};
    float time3{};
    float time4{};

};

// **************************** //

template<typename T, typename... Args>
auto Profiler::Timed(float& timeVar, const T& func, Args&... args) {
    float start = GetSystemTime();
    // --------------------------------------

    auto result = func(args...); // we run the given function

    // --------------------------------------
    float end = GetSystemTime();

    float elapsed = end - start;

    timeVar = elapsed;

    return result;
}

// **************************** //

template<typename T, typename... Args>
void* Profiler::TimedRunner(float& timeVar, const T& func, Args&... args) {
    // since returning void is causing problems, i'm transferring the func to an other one that returns void* through a lambda
    // (it's one way to do it)
    auto voidFunc = [=](Args&... args)
    {
        func(args...);
        return nullptr;
    };

    return Timed(timeVar, voidFunc, args...);
}

template<typename T, typename... Args>
auto Profiler::TimedSupplier(float& timeVar, const T& func, Args&... args) {
    return Timed(timeVar, func, args...);
}
