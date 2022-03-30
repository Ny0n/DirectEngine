#include "pch.h"

void PointLight::EngineStart()
{
    // light;    // create the light struct

    ZeroMemory(&light, sizeof(light));    // clear out the light struct for use

    light.Type = D3DLIGHT_POINT;
    //// light.Ambient = (D3DXCOLOR)D3DCOLOR_RGBA(0, 0, 0, 255);
    light.Ambient = (D3DXCOLOR)D3DCOLOR_RGBA(255, 100, 0, 255);
    //light.Diffuse = (D3DXCOLOR)D3DCOLOR_RGBA(255, 255, 0, 255);
    // light.Specular = (D3DXCOLOR)D3DCOLOR_RGBA(150, 150, 150, 255);
    light.Range = 100;    // light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    light.Attenuation0 = 0.0f;
    light.Attenuation1 = 0.1f;
    light.Attenuation2 = 0.0f;

    d3ddev->LightEnable(0, TRUE);    // turn on light #0
}

void PointLight::EngineUpdate()
{


    light.Position = transform->GetPosition() + transform->GetUp() * -5;

    d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
    // Create a direction for our light - it must be normalized
    // D3DXVECTOR3 g_lightDir = D3DXVECTOR3(0.0f, 0.6f, -0.8f);
    // light.Direction = g_lightDir;

    
    // d3ddev->LightEnable(0, TRUE);    // turn on light #0
    Utils::Println(transform->GetPosition().x);
    Utils::Println(transform->GetPosition().y);
    Utils::Println(transform->GetPosition().z);
}
