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
	// GetAxis()
	// GetAxisRaw()
	// GetMouseButton()
	// anyKey
	// anyKeyDown
	// anyKeyUp
	// mousePosition
private:
	friend class Engine;
	friend class Execution;

	struct InputState
	{
		bool key = false;
		bool keyDown = false;
		bool keyUp = false;
	};

	static map<KeyCode, InputState*> frameInputs;

	static void UpdateInputs();

	static void Clean();
};
