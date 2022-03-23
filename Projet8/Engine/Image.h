#pragma once

class Image final : public EngineComponent
{
public:
	const char* GetType() override { return NAMEOF(Image); }

	~Image() override;
	Image();

	void EngineStart() override;
	void EngineUpdate() override;

	LPCWSTR filePath;
	UINT height;
	UINT width;
	bool originalSize = false;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 rotationCenter;
	FLOAT rotation;

private:
	void Render();

	Canvas* _canvas;

	LPDIRECT3DTEXTURE9 ppTexture = nullptr;
	LPD3DXSPRITE ppSprite = nullptr;
};

