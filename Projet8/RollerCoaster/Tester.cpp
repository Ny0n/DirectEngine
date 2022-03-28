#include "Tester.h"

void Tester::Awake()
{
	Utils::Println("Awake " + to_string(Time::frameCount));
}

void Tester::OnEnable()
{
	Utils::Println("OnEnable " + to_string(Time::frameCount));
}

void Tester::Start()
{
	Utils::Println("Start " + to_string(Time::frameCount));
}

void Tester::Update()
{
	if (update)
	{
		Utils::Println("Update " + to_string(Time::frameCount));
		update = false;
	}
}

void Tester::LateUpdate()
{
	if (lateUpdate)
	{
		Utils::Println("LateUpdate " + to_string(Time::frameCount));
		lateUpdate = false;
	}
}

void Tester::OnDisable()
{
	Utils::Println("OnDisable " + to_string(Time::frameCount));
}

void Tester::OnDestroy()
{
	Utils::Println("OnDestroy " + to_string(Time::frameCount));
}
