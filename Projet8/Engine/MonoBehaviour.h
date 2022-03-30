#pragma once

class MonoBehaviour : public Component
{
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void Start() override {}
	void Update() override {}
	void LateUpdate() override {}
	void FixedUpdate() override {}

	void EngineStart() final {}
	void EngineUpdate() final {}
	void EngineUpdate2() final {}

public:
	MonoBehaviour() = default;
	
};
