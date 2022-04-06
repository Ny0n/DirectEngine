#pragma once

#define PROFILER_DISPLAY_ENABLED false   // Is the display enabled?
#define PROFILER_DISPLAY_COOLDOWN 1     // The time between each display in seconds, less or equal to the set FPS means every frame

// Only the Engine has an access to this class, since everything is private
class Profiler final {

    friend class Engine;
    friend class Time;

    Profiler();

    // *** Display *** //

    float _displayCooldown;

    void DisplayData();

    // *** Initialization *** //

    float _originalTime{};
    bool _isPreciseTime{};
    float _precisefrequency{};
    LONGLONG _originalPreciseTime{};

    void InitSystemTime();

    // *** Timing Methods *** //

    float GetSystemTime(); // Returns the current time since InitSystemTime() was last called
    float GetCurrentFPS();
    float GetFrameTime();

    template<typename T>
    void* TimedRunner(float& timeVar, const T& func);

    template<typename T>
    auto TimedSupplier(float& timeVar, const T& func);

    // *** Timing Data *** //

    int _loopCount{};
    
    float _lastFrameTime{-1};
    float _lastFixedTime{-1};
    float _lastDisplayTime{-1};

    float _dummyTime{};

    float _frameTime{};

    float _engineStartTime{};
    float _startTime{};
    float _fixedUpdateTime{};
    float _physicsTime{};
    float _inputTime{};
    float _updateTime{};
    float _lateUpdateTime{};
    float _engineUpdateTime{};
    float _presentTime{};

    float _time1{};
    float _time2{};
    float _time3{};
    float _time4{};

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
