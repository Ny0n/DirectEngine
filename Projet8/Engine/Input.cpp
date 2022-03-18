#include "pch.h"

map<KeyCode, Input::InputState*> Input::_frameInputs = {};

bool Input::GetKey(KeyCode key)
{
	return _frameInputs[key]->key;
}

bool Input::GetKeyDown(KeyCode key)
{
	return _frameInputs[key]->keyDown;
}

bool Input::GetKeyUp(KeyCode key)
{
	return _frameInputs[key]->keyUp;
}

void Input::UpdateInputs()
{
	for (auto code : KeyCodes)
	{
		InputState* state = _frameInputs[code.first];
		if (state == nullptr)
		{
			_frameInputs[code.first] = new InputState();
			state = _frameInputs[code.first];
		}

		const bool isDown = (GetAsyncKeyState(code.second) & 0x8000);

		state->keyDown = !state->key && isDown;
		state->keyUp = state->key && !isDown;
		state->key = isDown;
	}
}

void Input::Delete()
{
	for (auto code : _frameInputs)
	{
		delete(code.second);
	}
	_frameInputs.clear();
}
