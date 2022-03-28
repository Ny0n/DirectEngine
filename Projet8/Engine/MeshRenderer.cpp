#include "pch.h"

MeshRenderer::MeshRenderer(LPCWSTR path) : _pmesh(nullptr), _path(path)
{
}

MeshRenderer::~MeshRenderer()
{
    if(_pmesh != nullptr)
		_pmesh->Release();

    if (g_pMeshMaterials != nullptr)
        delete[] g_pMeshMaterials;

    if (g_pMeshTextures)
    {
        for (DWORD i = 0; i < g_dwNumMaterials; i++)
        {
            if (g_pMeshTextures[i])
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }
}

void MeshRenderer::EngineStart()
{
    // we load the mesh
    LPD3DXBUFFER pMtrlBuffer = nullptr;
    if (FAILED(D3DXLoadMeshFromX(_path, D3DXMESH_SYSTEMMEM, d3ddev, NULL, &pMtrlBuffer, NULL, &g_dwNumMaterials, &_pmesh))) {
        MessageBox(0, L"Failed to load mesh from disk", 0, 0);
        return;
    }

    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*) pMtrlBuffer->GetBufferPointer();
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    if (g_pMeshMaterials == NULL)
        return;
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if (g_pMeshTextures == NULL)
        return;

    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Copy the material
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

        g_pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {

            string pathTexture = "Mesh\\";
            pathTexture += d3dxMaterials[i].pTextureFilename;

            // Create the texture
            if (FAILED(D3DXCreateTextureFromFileA(d3ddev,
                pathTexture.c_str(),
                &g_pMeshTextures[i])))
            {
                MessageBox(0, L"Failed to load texture from disk", 0, 0);
            }
        }
    }

    // Done with the material buffer
    pMtrlBuffer->Release();
}

void MeshRenderer::EngineUpdate()
{
    if (_pmesh == nullptr)
        return;

    // we draw the mesh
    D3DXMATRIX finalMat = transform->GetMatrix();
    d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    // Meshes are divided into subsets, one for each material. Render them in
        // a loop
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        d3ddev->SetMaterial(&g_pMeshMaterials[i]);
        d3ddev->SetTexture(0, g_pMeshTextures[i]);

        // Draw the mesh subset
        _pmesh->DrawSubset(i);
    }
    if(g_dwNumMaterials == 0)
		_pmesh->DrawSubset(0);
}
