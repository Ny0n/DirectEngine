#include "SingletonTest.h"

SingletonTest* SceneSingleton<SingletonTest>::Instance;

SingletonTest::SingletonTest()
{
}

SingletonTest::~SingletonTest()
{
}

// **************************** //

// Start is called before the first frame update
void SingletonTest::Start()
{
}

// Update is called once per frame
void SingletonTest::Update()
{
	if (Input::GetKeyDown(KeyCode::N))
	{
		Utils::Println("SingletonTest");
	}
}
