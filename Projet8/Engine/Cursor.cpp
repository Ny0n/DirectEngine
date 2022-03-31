#include "pch.h"

LockMode Cursor::cursorLockMode = LockMode::None;

void Cursor::Lock()
{
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	cursorLockMode = LockMode::Locked;
}

void Cursor::Unlock()
{
	cursorLockMode = LockMode::None;
}

void Cursor::SetVisible(bool visibility)
{
	if (visibility)
		while (ShowCursor(true) < 0);
	else
		while (ShowCursor(false) >= 0);
}

void Cursor::CursorUpdate()
{
	switch (cursorLockMode)
	{
		case LockMode::Locked:
			{
				SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			}
			break;
		case LockMode::None:
			break;
	}
}
