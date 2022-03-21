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
    LPCWSTR _path;

};
