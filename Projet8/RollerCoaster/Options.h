#pragma once
#include "framework.h"

class Options final
{
public:
	Options() = delete;

	static bool showFps;
	static bool showTimer;
	static bool rotatingCrosshair;
	static bool pulsingCrosshair;
	static bool toggleAudio;

	static wstring pseudo;

	static float timerValue;
	static float playerSpeed;
};

