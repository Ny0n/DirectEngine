#pragma once

#include "Component.h"
#include "framework.h"

class MonoBehaviour : public Component
{

public:
	virtual ~MonoBehaviour() = default;

	virtual void start();
	virtual void update(float runTime, float deltaTime);
	
};
