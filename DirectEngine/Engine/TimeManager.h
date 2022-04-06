#pragma once

class Time final
{

public:
	Time() = delete;

	static float timeScale;		// The rate at which time passes (1 by default), this affects deltaTime and fixedDeltaTime (Read/Write)

	static const int& frameCount;		// The current frame number
	static const int& fixedUpdateCount; // The current fixed update number

	static const function<float()> runTime;		// The time in seconds since the start of the game
	static const function<float()> currentFps;	// The current FPS
	static const function<float()> frameTime;	// The time that took the last frame

	static const float& time;				// The time in seconds at the beginning of the new frame
	static const float& fixedTime;			// The time in seconds at the beginning of the new fixed update

	static const float& deltaTime;				// unscaledDeltaTime * timeScale
	static const float& unscaledDeltaTime;		// The time between the last frame and the current one

	static const float& fixedDeltaTime;			// fixedUnscaledDeltaTime / timeScale
	static const float& fixedUnscaledDeltaTime; // will ALWAYS return the set FixedTimestep

	static const bool& inSceneStep;			// Returns true if we are inside the <Scene Changes> step
	static const bool& inStartStep;			// Returns true if we are inside the Start() step
	static const bool& inUpdateStep;		// Returns true if we are inside the Update() step
	static const bool& inLateUpdateStep;	// Returns true if we are inside the LateUpdate() step
	static const bool& inFixedUpdateStep;	// Returns true if we are inside the FixedUpdate() step

private:
	friend class Engine;
	friend class Execution;

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

	static bool _inSceneStep;
	static bool _inStartStep;
	static bool _inUpdateStep;
	static bool _inLateUpdateStep;
	static bool _inFixedUpdateStep;

};
