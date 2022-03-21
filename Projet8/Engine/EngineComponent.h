#pragma once

extern list<const char*> unremovableEngineComponents; // defined in cpp

class EngineComponent : public Component
{
	// add newly created engine components here
	friend class Transform;
	friend class Camera;
	friend class MeshRenderer;
	friend class AlignedBox;
	friend class Collider;
	
	EngineComponent() = default;

public:
	ComponentCategory GetCategory() override { return ComponentCategory::single; }

	void Start() override {}
	void Update() override {}
	void LateUpdate() override {}
	void FixedUpdate() override {}

	void EngineStart() override {}
	void EngineUpdate() override {}

};
