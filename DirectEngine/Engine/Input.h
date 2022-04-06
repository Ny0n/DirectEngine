#pragma once

class Input final
{

public:
	Input() = delete;

	static bool GetKey(KeyCode key);
	static bool GetKeyDown(KeyCode key);
	static bool GetKeyUp(KeyCode key);
	static USHORT GetLastKeyDown();
	static void ResetLastKeyDown();

	static USHORT lastKeyDown;
private:
	friend class Engine;
	friend class Execution;

	static void UpdateInputs();
	static void Clean();

	struct InputState
	{
		bool key = false;
		bool keyDown = false;
		bool keyUp = false;
	};

	static map<KeyCode, InputState*> _frameInputs;
};
