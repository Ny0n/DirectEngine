#include "pch.h"

void Camera::EngineStart()
{
}

void Camera::EngineUpdate()
{
    // camera data

    auto pos = transform->GetPosition(); // the current position
    auto lookAt = pos + transform->GetForward(); // the look-at position (we look in front of us)
    auto camDir = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // the up direction

    auto fov = D3DXToRadian(45); // the horizontal field of view
    auto ratio = (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT; // aspect ratio
    auto nvp = 1.0f; // the near view-plane
    auto fvp = 100.0f; // the far view-plane

    // auto camDir = transform->GetRotation(); // the up direction
    // string s = "" + to_string(transform->GetRotation().x) + " " + to_string(transform->GetRotation().y) + " " + to_string(transform->GetRotation().z);
    // Utils::Println(s);

    // **************************** //

    d3ddev->SetFVF(CUSTOMFVF); // for the lightning

    D3DXMATRIX matView; // the view transform matrix
    D3DXMatrixLookAtLH(&matView, &pos, &lookAt, &camDir);
    d3ddev->SetTransform(D3DTS_VIEW, &matView); // set the view transform to matView

    D3DXMATRIX matProjection; // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection, fov, ratio, nvp, fvp);
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection); // set the projection

    // D3DXMATRIX matViewInversed;
    // D3DXMatrixInverse(&matViewInversed, NULL, &matView);
}
