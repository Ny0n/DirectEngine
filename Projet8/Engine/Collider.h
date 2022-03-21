#pragma once

class Collider final : public EngineComponent
{

public:
    const char* GetType() override { return NAMEOF(Collider); }
    ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

    bool IsColliding(Collider* other);

};
