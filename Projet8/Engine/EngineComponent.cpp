#include "pch.h"

list<string> EngineComponent::unremovableEngineComponents = { // components that we can't remove
	NAMEOF(Transform),
};
