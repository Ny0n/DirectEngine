#pragma once
#include "EngineLib.h"
class Target :
    public MonoBehaviour
{
    string GetType() override { return NAMEOF(Target); }

    
    void Update() override;

    list<GameObject*>* _listGameObject;

public:
    Target(list<GameObject*>* gos) { _listGameObject = gos; }
    void removeSelf();

    int points = 10;
};

