#pragma once
#include "GameObject.h"
class AlignedBox :
    public Component
{
    const char* GetType() override { return NAMEOF(AlignedBox); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }


    void Start() override;
    void Update(float runTime, float deltaTime) override;

    list<GameObject*> colliders;
public :
    list<GameObject*> AreIn(list<GameObject*> go);
};

