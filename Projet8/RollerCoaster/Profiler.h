#pragma once

#include <chrono>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class Profiler {

private:
    template<typename T, typename... Args>
    static auto timed(float& timeVar, T& func, Args&... args);

public:
    Profiler() {}

    template<typename T, typename... Args>
    static void* timedRunner(float& timeVar, T& func, Args&... args);

    template<typename T, typename... Args>
    static auto timedSupplier(float& timeVar, T& func, Args&... args);

    // *** Profiler Data *** //

    float runTime;

    float currentFPS;
    float currentFrameRate;

    float updateTime;

};

// **************************** //

template<typename T, typename... Args>
auto Profiler::timed(float& timeVar, T& func, Args&... args) {
    long long startMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    // --------------------------------------

    auto result = func(args...); // we run the given function

    // --------------------------------------
    long long endMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    long long elapsedMs = endMs - startMs;

    timeVar = elapsedMs / 1000.0f;

    return result;
}

// **************************** //

template<typename T, typename... Args>
void* Profiler::timedRunner(float& timeVar, T& func, Args&... args) {
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
auto Profiler::timedSupplier(float& timeVar, T& func, Args&... args) {
    return timed(timeVar, func, args...);
}
