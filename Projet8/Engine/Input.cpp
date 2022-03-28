#include "pch.h"

map<KeyCode, Input::InputState*> Input::frameInputs = {};

// **************************** //
USHORT Input::lastKeyDown = -1;

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

USHORT Input::GetLastKeyDown()
{
	return lastKeyDown;
}

void Input::ResetLastKeyDown()
{
	lastKeyDown = -1;
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

		bool isDown = false;
		if (Engine::GetInstance()->window == GetForegroundWindow()) // if our window has the focus
			isDown = (GetKeyState(code.second) & 0x8000);

		if (isDown && !state->key)
			lastKeyDown = code.second;

		state->keyDown = !state->key && isDown;
		state->keyUp = state->key && !isDown;
		state->key = isDown;
	}
}

void Input::Clean()
{
	Utils::DeleteMapSecond(frameInputs);
	frameInputs.clear();
}
