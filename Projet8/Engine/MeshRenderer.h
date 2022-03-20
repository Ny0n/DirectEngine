#pragma once

class MeshRenderer : public Component
{

public:
    const char* GetType() override { return NAMEOF(MeshRenderer); }
    ComponentCategory GetCategory() override { return ComponentCategory::unique; }

    MeshRenderer(LPCWSTR path);
    ~MeshRenderer() override;

    void Start() override;
    void Update() override;

private:
    ID3DXMesh* _pmesh;
    D3DMATERIAL9* g_pMeshMaterials = NULL; // Materials for our mesh
    LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
    LPCWSTR _path;
    DWORD  g_dwNumMaterials = 0L;
};
