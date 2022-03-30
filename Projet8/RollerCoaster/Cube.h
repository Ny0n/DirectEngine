#pragma once

#include "EngineLib.h"

class Cube : public MonoBehaviour
{
    string GetType() override { return NAMEOF(Cube); }

    void Update() override;
    ~Cube();
    Cube();
private:
    void CubeRender();
    void CubePlacement();

    LPDIRECT3DVERTEXBUFFER9 _vBuffer = nullptr;
    LPDIRECT3DINDEXBUFFER9  _iBuffer = nullptr;
};
