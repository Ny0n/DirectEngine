#include "pch.h"

list<const char*> EngineComponent::unremovableEngineComponents = { // components that we can't remove
	NAMEOF(Transform),
};
