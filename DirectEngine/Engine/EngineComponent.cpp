#include "pch.h"

const list<string> EngineComponent::_unremovableEngineComponents = { // components that we can't remove
	NAMEOF(Transform),
};
