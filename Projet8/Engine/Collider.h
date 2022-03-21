#pragma once
#include "Component.h"
class Collider :
    public Component
{
public:
    const char* GetType() override { return NAMEOF(Collider); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }
    bool IsColliding(Collider* other);
};

