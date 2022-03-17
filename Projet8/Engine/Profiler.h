#pragma once

#define PROFILER_DISPLAY_ENABLED true
#define PROFILER_DISPLAY_COOLDOWN 1 // less or equal to 0 means each frame

class Profiler final {

private:
    template<typename T>
    auto Timed(float& timeVar, const T& func);

    float _startTime{};
    bool _isPreciseTime{};
    float _frequency{};
    LONGLONG _startPreciseTime{};

    float _displayCooldown{};

public:
    Profiler() = default;

    void InitSystemTime();
    float GetSystemTime();
    void TryDisplayData();
    void DisplayData(); // forced instant display

    template<typename T>
    void* TimedRunner(float& timeVar, const T& func);

    template<typename T>
    auto TimedSupplier(float& timeVar, const T& func);

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
    float lastFrameTime{};

    int currentFrame{};
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

template<typename T>
auto Profiler::Timed(float& timeVar, const T& func) {
    float start = GetSystemTime();
    // --------------------------------------

    auto result = func(); // we run the given function

    // --------------------------------------
    float end = GetSystemTime();

    float elapsed = end - start;

    timeVar = elapsed;

    return result;
}

// **************************** //

template<typename T>
void* Profiler::TimedRunner(float& timeVar, const T& func) {
    // since returning void is causing problems, i'm transferring the func to an other one that returns void* through a lambda
    // (it's one way to do it)
    auto voidFunc = [=]()
    {
        func();
        return nullptr;
    };

    return Timed(timeVar, voidFunc);
}

template<typename T>
auto Profiler::TimedSupplier(float& timeVar, const T& func) {
    return Timed(timeVar, func);
}
