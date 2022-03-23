#pragma once

class EngineComponent : public Component
{
	// add newly created engine components here
	friend class Transform;
	friend class Camera;
	friend class MeshRenderer;
	friend class AlignedBox;
	friend class Collider;
	friend class Image;
	friend class Textbox;

	friend class GameObject;
	static list<const char*> unremovableEngineComponents;

	EngineComponent() = default;
	~EngineComponent() override { unremovableEngineComponents.clear(); } // TODO redo this (only once, clean)

public:
	ComponentCategory GetCategory() override { return ComponentCategory::single; }

	void Start() final {}
	void Update() final {}
	void LateUpdate() final {}
	void FixedUpdate() final {}

	void EngineStart() override {}
	void EngineUpdate() override {}

};
