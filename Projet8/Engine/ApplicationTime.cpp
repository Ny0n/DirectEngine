#include "pch.h"

Profiler* Time::_profiler = nullptr; // initialized by the engine

int Time::_frameCount = 0;

float Time::_time = 0.0f;

float Time::_deltaTime = 0.0f;
float Time::_unscaledDeltaTime = 0.0f;

float Time::_fixedDeltaTime = 0.0f;
float Time::_fixedUnscaledDeltaTime = 0.0f;

bool Time::_inStartStep = false;
bool Time::_inUpdateStep = false;
bool Time::_inFixedUpdateStep = false;

// **************************** //

float Time::timeScale = 1.0f;

const int& Time::frameCount = _frameCount;

const function<float()> Time::runTime = SUPPLIER(_profiler->GetSystemTime);
const float& Time::time = _time;

const float& Time::deltaTime = _deltaTime;
const float& Time::unscaledDeltaTime = _unscaledDeltaTime;

const float& Time::fixedDeltaTime = _fixedDeltaTime;
const float& Time::fixedUnscaledDeltaTime = _fixedUnscaledDeltaTime;

const bool& Time::inStartStep = _inStartStep;
const bool& Time::inUpdateStep = _inUpdateStep;
const bool& Time::inFixedUpdateStep = _inFixedUpdateStep;
