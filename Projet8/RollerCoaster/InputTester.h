#pragma once

#include "EngineLib.h"

class InputTester : public MonoBehaviour
{
	string GetType() override { return NAMEOF(InputTester); }

	void Start() override;
	void Update() override;
	void OnDestroy() override;

private:
	GameObject* tester = nullptr;

};
