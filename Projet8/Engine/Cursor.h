#pragma once

enum class LockMode
{
	None,
	Locked,
};

class Cursor final
{

public:
	Cursor() = delete;

	static void Lock();
	static void Unlock();

	static void SetVisible(bool visibility);

	static void CursorUpdate();

private:
	static LockMode cursorLockMode;

};
