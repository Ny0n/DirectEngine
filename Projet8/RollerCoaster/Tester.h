#pragma once

#include "EngineLib.h"

class Tester : public MonoBehaviour
{
	string GetType() override { return NAMEOF(Tester); }

	void Awake() override;
	void OnEnable() override;
	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void OnDisable() override;
	void OnDestroy() override;

private:
	bool update = true;
	bool lateUpdate = true;

};
