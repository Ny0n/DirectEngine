#pragma once

class Time final
{

public:
	Time() = delete;

	static const int& frameCount;
	static const float& runTime;
	static const float& deltaTime;

private:
	friend class Engine;

	static int _frameCount;
	static float _runTime;
	static float _deltaTime;

};
