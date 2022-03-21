#pragma once

extern list<const char*> engineDefaultComponentTypes; // defined in cpp

class EngineComponent : public Component
{
	friend class Transform;
	friend class Camera;
	friend class MeshRenderer;
	
	EngineComponent() = default;

public:
	ComponentCategory GetCategory() override { return ComponentCategory::single; }

	void Start() final {}
	void Update() final {}
	void LateUpdate() final {}
	void FixedUpdate() final {}

	void EngineStart() override {}
	void EngineUpdate() override {}

};
