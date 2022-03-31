#include "pch.h"

int PointLight::_nbLights = 0;

PointLight::PointLight(D3DXCOLOR color, float range, float attenuation): _color(color), _range(range), _attenuation(attenuation), _lightID(_nbLights)
{
    _nbLights += 1;
}

PointLight::~PointLight()
{
    if (_started)
        d3ddev->LightEnable(_lightID, FALSE); // turn off the light
}

// **************************** //

// EngineStart is called once, before the MonoBehaviour Start
void PointLight::EngineStart()
{
    // init the light struct

    ZeroMemory(&_light, sizeof(_light));    // clear out the light struct for use

    _light.Type = D3DLIGHT_POINT;

    _light.Ambient = _color;
    // _light.Diffuse = (D3DXCOLOR)D3DCOLOR_RGBA(255, 255, 0, 255);
    // _light.Specular = (D3DXCOLOR)D3DCOLOR_RGBA(150, 150, 150, 255);

    _light.Range = _range;    // light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    _light.Attenuation0 = 0.0f;
    _light.Attenuation1 = _attenuation;
    _light.Attenuation2 = 0.0f;

    d3ddev->SetLight(_lightID, &_light); // send the light struct properties to directx
	d3ddev->LightEnable(_lightID, TRUE); // turn on the light
    _started = true;
}

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void PointLight::EngineUpdate()
{
    _light.Position = transform->GetPosition() + offset();
    d3ddev->SetLight(_lightID, &_light); // we update the light properties
}
