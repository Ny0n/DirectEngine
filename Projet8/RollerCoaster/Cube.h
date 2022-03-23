#pragma once

#include "EngineLib.h"

class Cube : public MonoBehaviour
{

public :
	string GetType() override { return NAMEOF(Cube); }

    void Start() override;
    void Update() override;

private:
    void CubeRender();
    void CubePlacement();

};
