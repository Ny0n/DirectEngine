#include "pch.h"

map<KeyCode, Input::InputState*> Input::frameInputs = {};

// **************************** //

bool Input::GetKey(KeyCode key)
{
	return frameInputs[key]->key;
}

bool Input::GetKeyDown(KeyCode key)
{
	return frameInputs[key]->keyDown;
}

bool Input::GetKeyUp(KeyCode key)
{
	return frameInputs[key]->keyUp;
}

// **************************** //

void Input::UpdateInputs()
{
	for (auto code : OptimizedKeyCodes::table)
	{
		InputState* state = frameInputs[code.first];
		if (state == nullptr)
		{
			frameInputs[code.first] = new InputState();
			state = frameInputs[code.first];
		}

		const bool isDown = (GetAsyncKeyState(code.second) & 0x8000);

		state->keyDown = !state->key && isDown;
		state->keyUp = state->key && !isDown;
		state->key = isDown;
	}
}

void Input::Delete()
{
	for (auto code : frameInputs)
	{
		delete(code.second);
	}
	frameInputs.clear();
}
