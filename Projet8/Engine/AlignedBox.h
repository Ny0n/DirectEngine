#pragma once

class AlignedBox final : public EngineComponent
{
    list<Collider*> colliders;

public :
    string GetType() override { return NAMEOF(AlignedBox); }

    void EngineStart() override;

    list<Collider*> AreIn(list<GameObject*> go);

};
