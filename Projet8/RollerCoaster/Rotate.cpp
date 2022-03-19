#include "Rotate.h"

float InitDir(bool reverse)
{
    if (!reverse)
        return 1.0f;
    else
        return -1.0f;
}

Rotate::Rotate(float speed) : _speed(speed)
{
}

Rotate::Rotate(bool reverse) : _dir(InitDir(reverse))
{
}

Rotate::Rotate(float speed, bool reverse) : _speed(speed), _dir(InitDir(reverse))
{
}

// **************************** //

void Rotate::Update()
{
    transform->RotateRoll(_speed * _dir * Time::deltaTime);
}
