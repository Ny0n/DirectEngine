#pragma once
#include "EngineLib.h"
class Target :
    public MonoBehaviour
{
    string GetType() override { return NAMEOF(Target); }

    
    void Update() override;

    list<GameObject*>* _listGameObject;
    Transform* _LookAt;

public:
    Target(list<GameObject*>* gos) { _listGameObject = gos; }

    void removeSelf();
    void SetLookAt(Transform* LookAt) { _LookAt = LookAt; }

    int points = 10;
};

