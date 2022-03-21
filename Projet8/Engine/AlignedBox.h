#pragma once
#include "GameObject.h"
class AlignedBox :
    public Component
{
    const char* GetType() override { return NAMEOF(AlignedBox); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }


    void Start() override;
    void Update() override;

    list<Collider*> colliders;
public :
    list<Collider*> AreIn(list<GameObject*> go);
};

