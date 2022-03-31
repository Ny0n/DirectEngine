#include "pch.h"

void Camera::EngineStart()
{
}

void Camera::EngineUpdate()
{
    // camera data

    auto pos = transform->GetPosition(); // the current position
    auto lookAt = pos + transform->GetForward(); // the look-at position (we look in front of us)
    auto camDir = transform->GetUp(); // the up direction

    auto fov = D3DXToRadian(70); // the horizontal field of view
    auto ratio = (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT; // aspect ratio

    // **************************** //
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, _skyColor, 1.0f, 0); // background color

    d3ddev->SetFVF(CUSTOMFVF); // for the lightning

    D3DXMATRIX matView; // the view transform matrix
    D3DXMatrixLookAtLH(&matView, &pos, &lookAt, &camDir);
    d3ddev->SetTransform(D3DTS_VIEW, &matView); // set the view transform to matView

    D3DXMATRIX matProjection; // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection, fov, ratio, _nvp, _fvp);
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection); // set the projection
}

void Camera::ChangeFVP(float newFVP)
{
    _fvp = newFVP;
}

void Camera::ChangeNVP(float newNVP)
{
    _nvp = newNVP;
}

void Camera::ChangeSkyColor(D3DCOLOR skyColor)
{
    this->_skyColor = skyColor;
}
