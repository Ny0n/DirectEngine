#pragma once
#include "EngineLib.h"


class Shoot :
    public MonoBehaviour
{
public:
	string GetType() override { return NAMEOF(Shoot); }
	void Start() override;
	void Update() override;
};

