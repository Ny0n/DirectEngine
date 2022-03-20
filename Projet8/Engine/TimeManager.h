#pragma once

class Time final
{

public:
	Time() = delete;

	static float timeScale;		// The rate at which time passes (1 by default), this affects deltaTime and fixedDeltaTime (Read/Write)

	static const int& frameCount;		// The current frame number
	static const int& fixedUpdateCount; // The current fixed update number

	static const function<float()> runTime;	// The time in seconds since the start of the game
	static const float& time;				// The time in seconds at the beginning of the new frame
	static const float& fixedTime;			// The time in seconds at the beginning of the new fixed update

	static const float& deltaTime;
	static const float& unscaledDeltaTime;

	static const float& fixedDeltaTime;
	static const float& fixedUnscaledDeltaTime;

	static const bool& inStartStep;			// Returns true if called inside a Start() callback
	static const bool& inUpdateStep;		// Returns true if called inside an Update() callback
	static const bool& inFixedUpdateStep;	// Returns true if called inside a FixedUpdate() callback

private:
	friend class Engine;

	static Profiler* _profiler; // to have access to the GetSystemTime() function

	// all of those must be filled by the Engine

	static int _frameCount;
	static int _fixedUpdateCount;

	static float _time;
	static float _fixedTime;

	static float _deltaTime;
	static float _unscaledDeltaTime;

	static float _fixedDeltaTime;
	static float _fixedUnscaledDeltaTime;

	static bool _inStartStep;
	static bool _inUpdateStep;
	static bool _inFixedUpdateStep;

};
