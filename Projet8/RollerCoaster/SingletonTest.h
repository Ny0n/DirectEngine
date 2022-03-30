#pragma once

#include "EngineLib.h"
#include "SceneSingleton.h"

class SingletonTest : public SceneSingleton<SingletonTest>
{
	string GetType() override { return NAMEOF(SingletonTest); }

	void Start() override;
	void Update() override;

	bool DontDestroyOnLoad() override { return false; }

public:
	SingletonTest();
	~SingletonTest() override;
	
};
