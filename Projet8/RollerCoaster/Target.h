#pragma once
#include "EngineLib.h"
class Target :
    public MonoBehaviour
{
    string GetType() override { return NAMEOF(Target); }

    void Update() override;

public:
    Target(list<GameObject*>* gos) { _pListGameObject = gos; }

    void removeSelf();

    void SetLookAt(Transform* LookAt) { _pLookAt = LookAt; }

    int points = 10;
private :
    Transform* _pLookAt;

    list<GameObject*>* _pListGameObject;
};

