#include "InputTester.h"

void InputTester::Update(float runTime, float deltaTime)
{
	if (Input::GetKey(KeyCode::A))
	{
		Utils::Println("A");
	}

	if (Input::GetKeyUp(KeyCode::A))
	{
		Utils::Println("A Up");
	}

	if (Input::GetKeyDown(KeyCode::A))
	{
		Utils::Println("A Down");
	}

	if (Input::GetKeyDown(KeyCode::Escape))
		Application::Quit();
}
