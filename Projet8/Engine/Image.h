#pragma once

class Image final : public Canvas
{
public:
	const char* GetType() override { return NAMEOF(Image); }
	~Image() override;

	void EngineStart() override;
	void Render() override;

	IDirect3DSurface9* surface;
	LPCWSTR filePath;
	UINT height;
	UINT width;
	bool originalSize = false;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 rotation;
};

