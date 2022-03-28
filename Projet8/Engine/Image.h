#pragma once

class Image final : public EngineComponent
{
	void EngineStart() override;
	void EngineUpdate() override;

public:
	string GetType() override { return NAMEOF(Image); }

	~Image() override;
	Image();

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
