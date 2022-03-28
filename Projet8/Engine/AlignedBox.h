#pragma once

class AlignedBox final : public EngineComponent
{
    string GetType() override { return NAMEOF(AlignedBox); }

    void EngineStart() override;

public :
    list<Collider*> AreIn(list<GameObject*> go);

private:
    list<Collider*> colliders;

};
