#pragma once

class Collider final : public EngineComponent
{

public:
    Collider();
    ~Collider() override;

	string GetType() override { return NAMEOF(Collider); }
    ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

public:
    bool IsColliding(Collider* other);

    void AddCollideWith(Collider* collide) { _collidersWith.push_back(collide); }
    void RemoveCollideWith(Collider* collide);
    list<Collider*> GetCollidersWith() { return _collidersWith; }


private:
    list<Collider*> _collidersWith;
};
