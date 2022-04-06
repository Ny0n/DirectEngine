#pragma once

class MeshRenderer final : public EngineComponent
{
    string GetType() override { return NAMEOF(MeshRenderer); }

    void EngineStart() override;
    void EngineUpdate() override;

public:
    MeshRenderer(LPCWSTR path);
    ~MeshRenderer() override;

private:
    ID3DXMesh* _pmesh;
    D3DMATERIAL9* _pMeshMaterials = NULL; // Materials for our mesh
    LPDIRECT3DTEXTURE9* _pMeshTextures = NULL; // Textures for our mesh
    LPCWSTR _path;
    DWORD  _dwNumMaterials = 0L;

};
