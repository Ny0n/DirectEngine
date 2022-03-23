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
	friend class Canvas;
	friend class Image;

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
