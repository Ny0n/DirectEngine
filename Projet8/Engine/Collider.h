#pragma once

class Collider final : public EngineComponent
{

public:
    Collider();
    ~Collider() override;

	string GetType() override { return NAMEOF(Collider); }
    ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

    bool IsColliding(Collider* other);

    void AddCollideWith(Collider* collide) { collidersWith.push_back(collide); }
    void RemoveCollideWith(Collider* collide);
    list<Collider*> GetCollidersWith() { return collidersWith; }


private:
    list<Collider*> collidersWith;
};
