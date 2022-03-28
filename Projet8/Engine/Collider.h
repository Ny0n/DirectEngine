#pragma once

class Collider final : public EngineComponent
{
    string GetType() override { return NAMEOF(Collider); }
    ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

public:
    bool IsColliding(Collider* other);

};
