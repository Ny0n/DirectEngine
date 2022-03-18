#include "InputTester.h"

void InputTester::Update(float runTime, float deltaTime)
{
	if (GetAsyncKeyState(KeyCode::A) & 0x8000)
	{
		Utils::Println("A");
	}
}
