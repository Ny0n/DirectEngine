#pragma once

class Textbox final : public EngineComponent
{
	void EngineStart() override;
	void EngineUpdate() override;

public:
	string GetType() override { return NAMEOF(Textbox); }

	explicit Textbox();
	~Textbox() override;

	INT fontHeight = 25;
	UINT fontWidth = 0;
	UINT fontWeight = FW_NORMAL;
	BOOL fontItalic = false;
	LPCWSTR textFont = L"Arial";

	wstring text = L"Default text!";
	DWORD textFormat = DT_CENTER | DT_VCENTER;

	LPCWSTR boxFilepath = L"Image\\blanc.png";

	D3DXVECTOR2 rectTopLeft = {0,0 };
	D3DXVECTOR2 rectBottomRight = { 200, 50 };

	D3DCOLOR borderColor = D3DCOLOR_ARGB(255, 255, 166, 0);
	D3DCOLOR boxColor = D3DCOLOR_ARGB(255, 0, 255, 255);
	D3DCOLOR textColor = D3DCOLOR_ARGB(255, 255, 0, 255);

	FLOAT borderThickness = 5;

	bool drawBox = false;
	bool drawBorder = false;
	

private:
	void Render();

	UINT width;
	UINT height;

	ID3DXLine* line = nullptr;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE ppSprite = nullptr;
	RECT textRect;
	ID3DXFont* font = nullptr;
};

