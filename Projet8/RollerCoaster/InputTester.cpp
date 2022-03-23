#include "InputTester.h"

#include "GoUp.h"
#include "Move.h"

void InputTester::Start()
{
	// Utils::Println("Start");
	// Component* comp = new EngineComponent();
}

// static int test = 0;

void InputTester::Update()
{
	// test = 0;
	// Utils::Println("Update");
	// Utils::Println(to_string(Time::runTime()));
	// Utils::Println(to_string(Time::deltaTime));
	// Utils::Println(to_string(Time::unscaledDeltaTime));
	// Utils::Println(to_string(Time::frameCount));
	// Utils::Println(to_string(Time::inStartStep));
	// Utils::Println(to_string(Time::inUpdateStep));

	static int i = SceneManager::GetActiveSceneIndex();
	if (Input::GetKeyDown(KeyCode::F))
	{
		i++;
		if (i > SceneManager::BuildScenesCount())
			i = 1;

		SceneManager::LoadScene(i);

		// string name = SceneManager::GetActiveSceneName();
		// if (name == "MenuScene")
		// 	SceneManager::LoadScene("DefaultScene");
		// if (name == "DefaultScene")
		// 	SceneManager::LoadScene("MenuScene");
	}

	if (Input::GetKeyDown(KeyCode::R))
	{
		SceneManager::LoadScene(SceneManager::GetActiveSceneName());
	}

	if (Input::GetKeyDown(KeyCode::A))
	{
		auto comp = gameObject->GetComponent<Move>();
		if (comp != nullptr)
		{
			comp->speed *= 2;
			Utils::Println("Found");
		}
	}

	// if (Input::GetKeyDown(KeyCode::Y))
	// {
	// 	SceneManager::LoadSceneAdditive("MenuScene");
	// }
	// if (Input::GetKeyDown(KeyCode::U))
	// {
	// 	SceneManager::UnloadScene("MenuScene");
	// }

	// ********** //

	// if (Input::GetKeyDown(KeyCode::T))
	// {
	// 	Time::timeScale = 0.5f;
	// }
	//
	// if (Input::GetKeyUp(KeyCode::T))
	// {
	// 	Time::timeScale = 1.0f;
	// }
	//
	// if (Input::GetKeyDown(KeyCode::A))
	// {
	// 	Utils::Println("Key Down");
	// }
	//
	// if (Input::GetKey(KeyCode::A))
	// {
	// 	Utils::Println("Key");
	// }
	//
	// if (Input::GetKeyUp(KeyCode::A))
	// {
	// 	Utils::Println("Key Up");
	// }

	if (Input::GetKeyDown(KeyCode::Escape))
		Application::Quit();
}

void InputTester::OnDestroy()
{
	// Utils::Println("OnDestroy");
}

// void InputTester::LateUpdate()
// {
// 	// test = 0;
// 	// Utils::Println("LateUpdate");
// }

// void InputTester::FixedUpdate()
// {
// 	// test++;
// 	// Utils::Println("FixedUpdate " + to_string(test));
// 	// Utils::Println("FixedUpdate");
// 	// Utils::Println(to_string(Time::runTime()));
// 	// Utils::Println(to_string(Time::fixedTime));
// 	// Utils::Println(to_string(Time::fixedDeltaTime));
// 	// Utils::Println(to_string(Time::fixedUnscaledDeltaTime));
// 	// Utils::Println(to_string(Time::fixedUpdateCount));
// 	// Utils::Println(to_string(Time::inStartStep));
// 	// Utils::Println(to_string(Time::inUpdateStep));
// 	// Utils::Println(to_string(Time::inFixedUpdateStep));
// }

// void InputTester::EngineStart()
// {
//
// }
