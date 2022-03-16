#include "pch.h"

#include "EngineLib.h"

MeshRenderer::MeshRenderer(LPCWSTR path) : _pmesh(nullptr), _path(path)
{
}

MeshRenderer::~MeshRenderer()
{
    _pmesh->Release();
}

void MeshRenderer::Start()
{
    // we load the mesh
    LPD3DXBUFFER pMtrlBuffer = nullptr;
    DWORD  g_dwNumMaterials = 0L;
    if (FAILED(D3DXLoadMeshFromX(_path, D3DXMESH_SYSTEMMEM, d3ddev, NULL, &pMtrlBuffer, NULL, &g_dwNumMaterials, &_pmesh))) {
        MessageBox(0, L"Failed to load mesh from disk", 0, 0);
    }
}

void MeshRenderer::Update(float runTime, float deltaTime)
{
    if (_pmesh == nullptr)
        return;

    // we draw the mesh
    D3DXMATRIX finalMat = transform->GetMatrix();
    d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    _pmesh->DrawSubset(0);
}
