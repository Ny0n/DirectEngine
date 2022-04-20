#include "pch.h"

MeshRenderer::MeshRenderer(LPCWSTR path) : _pmesh(nullptr), _path(path)
{
}

MeshRenderer::~MeshRenderer()
{
    if(_pmesh != nullptr)
		_pmesh->Release();

    if (_pMeshMaterials != nullptr)
        delete[] _pMeshMaterials;

    if (_pMeshTextures)
    {
        for (DWORD i = 0; i < _dwNumMaterials; i++)
        {
            if (_pMeshTextures[i])
                _pMeshTextures[i]->Release();
        }
        delete[] _pMeshTextures;
    }
}

void MeshRenderer::EngineStart()
{
    // we load the mesh
    LPD3DXBUFFER pMtrlBuffer = nullptr;
    if (FAILED(D3DXLoadMeshFromX(_path, D3DXMESH_SYSTEMMEM, d3ddev, NULL, &pMtrlBuffer, NULL, &_dwNumMaterials, &_pmesh))) {
        MessageBox(0, L"Failed to load mesh from disk", 0, 0);
        return;
    }

    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*) pMtrlBuffer->GetBufferPointer();
    _pMeshMaterials = new D3DMATERIAL9[_dwNumMaterials];
    if (_pMeshMaterials == NULL)
        return;
    _pMeshTextures = new LPDIRECT3DTEXTURE9[_dwNumMaterials];
    if (_pMeshTextures == NULL)
        return;

    for (DWORD i = 0; i < _dwNumMaterials; i++)
    {
        // Copy the material
        _pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        _pMeshMaterials[i].Ambient = _pMeshMaterials[i].Diffuse;
        // _pMeshMaterials[i].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

        _pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {

            string pathTexture = "Mesh\\";
            pathTexture += d3dxMaterials[i].pTextureFilename;

            // Create the texture
            if (FAILED(D3DXCreateTextureFromFileA(d3ddev,
                pathTexture.c_str(),
                &_pMeshTextures[i])))
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
    // Meshes are divided into subsets, one for each material. Render them in a loop
    for (DWORD i = 0; i < _dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        d3ddev->SetMaterial(&_pMeshMaterials[i]);
        d3ddev->SetTexture(0, _pMeshTextures[i]);

        // Draw the mesh subset
        _pmesh->DrawSubset(i);
    }
}
