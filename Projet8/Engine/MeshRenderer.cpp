#include "pch.h"

#include "EngineLib.h"

MeshRenderer::MeshRenderer(LPCWSTR path) : _pmesh(nullptr), _path(path)
{
}

MeshRenderer::~MeshRenderer()
{
    //delete _pmesh;
}

void MeshRenderer::Update(float runTime, float deltaTime)
{
    Render();
    Placement();
    static float index = 0; index += 5;
    transform->RotateRoll(50*deltaTime);
    D3DXVECTOR3 pos = transform->GetPosition();
    pos.y += 1*deltaTime;
    transform->SetPosition(pos);
}

void MeshRenderer::Render()
{
    
    LPD3DXBUFFER pMtrlBuffer = NULL;
    int pAdjBuffer = 0;
    /*strcpy(filepath, "C:/Users/fcalvet/Desktop/direct8/Projet8/RollerCoaster/Mesh");
    strcat(filepath, "radioflyer.x");*/
    DWORD  g_dwNumMaterials = 0L;
    //HRESULT h = D3DXLoadMeshFromX(L"C:\\Users\\fcalvet\\Desktop\\direct8\\Projet8\\RollerCoaster\\Mesh\\radioflyer.x", D3DXMESH_SYSTEMMEM, d3ddev, NULL, &pMtrlBuffer, NULL, &g_dwNumMaterials, &m_pmesh);
    //DXTRACE_ERR(L"Failed to load mesh.", h);
    if (FAILED(D3DXLoadMeshFromX(_path, D3DXMESH_SYSTEMMEM, d3ddev, NULL, &pMtrlBuffer, NULL, &g_dwNumMaterials, &_pmesh))) {
        MessageBox(0, L"load mesh fail ", 0, 0);
        return;
    }
}

void MeshRenderer::Placement()
{
    //D3DXMATRIX matTranslate;    // a matrix to store the translation information

    //// build a matrix to move the model 12 units along the x-axis and 4 units along the y-axis
    //// store it to matTranslate
    //D3DXMATRIX matRotate;
    //D3DXMATRIX matRotateX;
    //D3DXMATRIX matRotateY;
    //D3DXMATRIX matRotateZ;
    //D3DXMATRIX matScale;
    //D3DXMATRIX finalMat;
    ////D3DXMATRIX matTranslate;
    //D3DXMatrixIdentity(&matRotateX);
    ////D3DXMatrixIdentity(&matRotateY);
    //D3DXMatrixIdentity(&matRotateZ);
    //D3DXMatrixIdentity(&matScale);
    //D3DXMatrixIdentity(&matTranslate);
    //D3DXQUATERNION quat = transform->GetQuaternion();
    //D3DXMatrixRotationX(&matRotateX, quat.x);
    //D3DXMatrixRotationY(&matRotateY, quat.y);    // the front side
    //D3DXMatrixRotationZ(&matRotateZ, quat.z);
    //D3DXVECTOR3 scale = transform->GetScale();
    //D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
    //D3DXVECTOR3 position = transform->GetPosition();
    //D3DXMatrixTranslation(&matTranslate, position.x,position.y, position.z);

    //matRotate = matRotateX;
    //matRotate *= matRotateY;
    //matRotate *= matRotateZ;

    //finalMat = matRotate;

    //finalMat *= matTranslate;



    //finalMat *= matScale;


    ////d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    ////d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    ////d3ddev->SetTransform(D3DTS_WORLD, &finalMatB);
    ////d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    //// draw the Hypercraft
    //d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    D3DXMATRIX finalMat = transform->GetMatrix();
    d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    _pmesh->DrawSubset(0);
    _pmesh->Release();
}
