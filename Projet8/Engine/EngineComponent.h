#pragma once

class EngineComponent : public Component
{
	friend class GameObject;
	static const list<string> unremovableEngineComponents;

public:
	EngineComponent() = default; // TEMPORARY, while we're actively coding
	ComponentCategory GetCategory() override { return ComponentCategory::single; }

	void Start() final {}
	void Update() final {}
	void LateUpdate() final {}
	void FixedUpdate() final {}

	void EngineStart() override {}
	void EngineUpdate() override {}

};
