#pragma once
#include "Component.h"
#include "Transform.h"
#include "framework.h"
#include "GameObject.h"
class Cube :
    public Component
{
public :

    Cube(GameObject* g, float size);
    void Start();
    void Update(float runTime, float deltaTime);

    void cubeRender();

    Transform* _Transform;
    float _Size;



};

