#pragma once
#include "EngineComponent.h"
class PointLight :
    public EngineComponent
{
    string GetType() override { return NAMEOF(PointLight); }
 /*   PointLight(D3DXCOLOR color,)*/
    void EngineStart() override;
    void EngineUpdate() override;
    static int nbreLight;
    D3DLIGHT9 light;
    int idLight;
};

