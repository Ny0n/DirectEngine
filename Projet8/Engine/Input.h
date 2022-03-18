#pragma once

class Input final
{

	struct InputState
	{
		bool key = false;
		bool keyDown = false;
		bool keyUp = false;
	};

	static map<KeyCode, InputState*> _frameInputs;

public:
	Input() = delete;
	
	static bool GetKey(KeyCode key);
	static bool GetKeyDown(KeyCode key);
	static bool GetKeyUp(KeyCode key);

	static void UpdateInputs();
	static void Delete();

};
