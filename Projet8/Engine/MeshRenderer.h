#pragma once

class MeshRenderer final : public EngineComponent
{

public:
    const char* GetType() override { return NAMEOF(MeshRenderer); }

    MeshRenderer(LPCWSTR path);
    ~MeshRenderer() override;

    void EngineStart() override;
    void EngineUpdate() override;

private:
    ID3DXMesh* _pmesh;
    D3DMATERIAL9* g_pMeshMaterials = NULL; // Materials for our mesh
    LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
    LPCWSTR _path;
    DWORD  g_dwNumMaterials = 0L;

};
