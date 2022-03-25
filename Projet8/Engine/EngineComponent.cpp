#include "pch.h"

const list<string> EngineComponent::unremovableEngineComponents = { // components that we can't remove
	NAMEOF(Transform),
};
