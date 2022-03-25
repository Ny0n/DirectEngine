#pragma once

class Collider final : public EngineComponent
{

public:
	string GetType() override { return NAMEOF(Collider); }
    ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

    bool IsColliding(Collider* other);

};
