#include "pch.h"
#include "Cursor.h"


LockMode Cursor::cursorLockMode = LockMode::None;

void Cursor::Lock()
{
	cursorLockMode = LockMode::Locked;
}

void Cursor::Unlock()
{
	cursorLockMode = LockMode::None;
}

void Cursor::SetVisible(bool visibility)
{
	ShowCursor(visibility);
}

void Cursor::CursorUpdate()
{
	switch (cursorLockMode)
	{
	case LockMode::Locked:
		{
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		} break;
	case LockMode::None:
	default:
		break;
	}
}
