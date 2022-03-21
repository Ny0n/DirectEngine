#pragma once

class MonoBehaviour : public Component
{

public:
	MonoBehaviour() = default;
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void Start() override {}
	void Update() override {}
	void LateUpdate() override {}
	void FixedUpdate() override {}

	void EngineStart() final {}
	void EngineUpdate() final {}

};
