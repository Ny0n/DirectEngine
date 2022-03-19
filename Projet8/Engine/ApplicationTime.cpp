#include "pch.h"

int Time::_frameCount = 0;
float Time::_runTime = 0.0f;
float Time::_deltaTime = 0.0f;

// **************************** //

const int& Time::frameCount = _frameCount;
const float& Time::runTime = _runTime;
const float& Time::deltaTime = _deltaTime;
