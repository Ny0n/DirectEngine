#include "pch.h"

Profiler* Time::_profiler = nullptr; // initialized by the Engine

int Time::_frameCount = 0;
int Time::_fixedUpdateCount = 0;

float Time::_time = 0.0f;
float Time::_fixedTime = 0.0f;

float Time::_deltaTime = 0.0f;
float Time::_unscaledDeltaTime = 0.0f;

float Time::_fixedDeltaTime = 0.0f;
float Time::_fixedUnscaledDeltaTime = 0.0f;

bool Time::_inSceneStep = false;
bool Time::_inStartStep = false;
bool Time::_inUpdateStep = false;
bool Time::_inLateUpdateStep = false;
bool Time::_inFixedUpdateStep = false;

// **************************** //

float Time::timeScale = 1.0f;

const int& Time::frameCount = _frameCount;
const int& Time::fixedUpdateCount = _fixedUpdateCount;

const Supplier(float) Time::runTime = SUPPLIER(_profiler->GetSystemTime());
const Supplier(float) Time::currentFps = SUPPLIER(_profiler->GetCurrentFPS());
const Supplier(float) Time::frameTime = SUPPLIER(_profiler->GetFrameTime());

const float& Time::time = _time;
const float& Time::fixedTime = _fixedTime;

const float& Time::deltaTime = _deltaTime;
const float& Time::unscaledDeltaTime = _unscaledDeltaTime;

const float& Time::fixedDeltaTime = _fixedDeltaTime;
const float& Time::fixedUnscaledDeltaTime = _fixedUnscaledDeltaTime;

const bool& Time::inSceneStep = _inSceneStep;
const bool& Time::inStartStep = _inStartStep;
const bool& Time::inUpdateStep = _inUpdateStep;
const bool& Time::inLateUpdateStep = _inLateUpdateStep;
const bool& Time::inFixedUpdateStep = _inFixedUpdateStep;
