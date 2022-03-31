#pragma once

class Textbox final : public EngineComponent
{
	string GetType() override { return NAMEOF(Textbox); }
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void EngineStart() override;
	void EngineUpdate() override;

public:
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

	D3DXVECTOR2 position = { 0,0 };
	D3DXVECTOR2 size = { 200, 50 };

	D3DCOLOR borderColor = D3DCOLOR_ARGB(255, 255, 166, 0);
	D3DCOLOR boxColor = D3DCOLOR_ARGB(255, 0, 255, 255);
	D3DCOLOR textColor = D3DCOLOR_ARGB(255, 255, 0, 255);

	FLOAT borderThickness = 5;

	bool drawBox = false;
	bool drawBorder = false;

private:
	void Render();
	
	D3DXVECTOR2 _rectTopLeft;
	D3DXVECTOR2 _rectBottomRight;

	ID3DXLine* _pLine = nullptr;
	LPDIRECT3DTEXTURE9 _texture;
	LPD3DXSPRITE _sprite = nullptr;
	RECT _textRect;
	ID3DXFont* _pFont = nullptr;
};

