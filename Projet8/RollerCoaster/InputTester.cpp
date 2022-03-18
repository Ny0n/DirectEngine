#include "InputTester.h"

void InputTester::Update(float runTime, float deltaTime)
{
	if (Input::GetKeyDown(KeyCode::A))
	{
		Utils::Println("Key Down");
	}

	if (Input::GetKey(KeyCode::A))
	{
		Utils::Println("Key");
	}

	if (Input::GetKeyUp(KeyCode::A))
	{
		Utils::Println("Key Up");
	}

	if (Input::GetKeyDown(KeyCode::Escape))
		Application::Quit();
}
