#pragma once
#include "Component.h"
#include "Transform.h"
#include "framework.h"
#include "GameObject.h"
#include "Utils.h"

class Cube :
    public Component
{
public :

    Cube(GameObject* g, float size);
    void Start();
    void Update(float runTime, float deltaTime);

    void cubeRender();
    void cubePlacement();

    Transform* _Transform;
    float _Size;
    //LPDIRECT3DVERTEXBUFFER9 _VBuffer;    // the pointer to the vertex buffer
    //LPDIRECT3DINDEXBUFFER9 _IBuffer;    // the pointer to the index buffer


};

