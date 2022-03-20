#pragma once

#define PROFILER_DISPLAY_ENABLED true   // Is the display enabled?
#define PROFILER_DISPLAY_COOLDOWN 1     // The time between each display in seconds, less or equal to 0 means every frame

// Only the Engine has an access to this class, since everything is private
class Profiler final {

    friend class Engine;
    friend class Time;

    Profiler();

    // *** Display *** //

    float displayCooldown;

    void DisplayData();

    // *** Initialization *** //

    float originalTime{};
    bool isPreciseTime{};
    float precisefrequency{};
    LONGLONG originalPreciseTime{};

    void InitSystemTime();

    // *** Timing Methods *** //

    float GetSystemTime(); // Returns the current time since InitSystemTime() was last called

    template<typename T>
    void* TimedRunner(float& timeVar, const T& func);

    template<typename T>
    auto TimedSupplier(float& timeVar, const T& func);

    // *** Timing Data *** //

    // void AddFPS(float fpsIn);

    int loopCount{};
    float currentFPS{};

    float currentFrameRate{};
    float lastFrameTime{-1};
    float currentFixedRate{};
    float lastFixedTime{-1};
    float lastDisplayTime{-1};

    float frameTime{};
    float inputTime{};
    float startTime{};
    float updateTime{};
    float fixedUpdateTime{};
    float presentTime{};

    float time1{};
    float time2{};
    float time3{};
    float time4{};

};

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

    return TimedSupplier(timeVar, voidFunc);
}

template<typename T>
auto Profiler::TimedSupplier(float& timeVar, const T& func) {
	const float start = GetSystemTime();
    // --------------------------------------

    auto result = func(); // we run the given function

    // --------------------------------------
	const float end = GetSystemTime();

	const float elapsed = end - start;

    timeVar = elapsed;

    return result;
}
