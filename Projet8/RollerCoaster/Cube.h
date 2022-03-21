#pragma once

#include "EngineLib.h"

class Cube : public MonoBehaviour
{

public :
    const char* GetType() override { return NAMEOF(Cube); }

    void Start() override;
    void Update() override;

private:
    void CubeRender();
    void CubePlacement();

};
