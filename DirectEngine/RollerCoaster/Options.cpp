#include "Options.h"

bool Options::showFps = true;

bool Options::showTimer = true;
bool Options::rotatingCrosshair = true;
bool Options::pulsingCrosshair = true;
bool Options::toggleAudio = false;
bool Options::showScore = true;

wstring Options::pseudo = L"Default User";

float Options::timerValue = 30.0f;
float Options::playerSpeed = 25.0f;

int Options::scoreMin = 100;