#include "InputTester.h"

void InputTester::Update(float runTime, float deltaTime)
{
	if (Input::GetKey(KeyCode::A))
	{
		Utils::Println("A");
	}
}
