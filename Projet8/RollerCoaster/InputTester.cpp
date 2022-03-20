#include "InputTester.h"

void InputTester::Start()
{
	// Utils::Println("Start");
}

void InputTester::Update()
{
	// Utils::Println("Update");
	// Utils::Println(to_string(Time::runTime()));
	// Utils::Println(to_string(Time::deltaTime));
	// Utils::Println(to_string(Time::unscaledDeltaTime));
	// Utils::Println(to_string(Time::frameCount));
	// Utils::Println(to_string(Time::inStartStep));
	// Utils::Println(to_string(Time::inUpdateStep));

	if (Input::GetKeyDown(KeyCode::T))
	{
		Time::timeScale = 0.0f;
	}

	if (Input::GetKeyUp(KeyCode::T))
	{
		Time::timeScale = 1.0f;
	}

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

void InputTester::FixedUpdate()
{
	// Utils::Println("FixedUpdate");
	// Utils::Println(to_string(Time::runTime()));
	// Utils::Println(to_string(Time::fixedTime));
	// Utils::Println(to_string(Time::fixedDeltaTime));
	// Utils::Println(to_string(Time::fixedUnscaledDeltaTime));
	// Utils::Println(to_string(Time::fixedUpdateCount));
	// Utils::Println(to_string(Time::inStartStep));
	// Utils::Println(to_string(Time::inUpdateStep));
	// Utils::Println(to_string(Time::inFixedUpdateStep));
}