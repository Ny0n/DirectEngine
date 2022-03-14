#include "pch.h"

#include "Camera.h"

void Camera::Update(float runTime, float deltaTime)
{
    d3ddev->SetFVF(CUSTOMFVF);

    D3DXMATRIX matView;    // the view transform matrix

    static float index = 0.0f;
    index += 0.05f; // an ever-increasing float value

    auto camPos = D3DXVECTOR3(0, 0, 30.0f);    // the camera position
    auto lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // the look-at position
    auto camDir = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // the up directions

    D3DXMatrixLookAtLH(&matView, &camPos, &lookAt, &camDir);  // the up direction
    float det;
    D3DXMATRIX matViewInversed;
    D3DXMatrixInverse(&matViewInversed, NULL, &matView);
    d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    D3DXMATRIX matProjection;     // the projection transform matrix

    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
        1.0f,    // the near view-plane
        100.0f);    // the far view-plane

    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
}
