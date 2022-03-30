#pragma once

class Button : public EngineComponent
{
public:
	Button();
	~Button() override;
	function<void()> onClick = nullptr;

	INT fontHeight = 25;
	UINT fontWidth = 0;
	UINT fontWeight = FW_NORMAL;
	BOOL fontItalic = false;
	LPCWSTR textFont = L"Arial";
	wstring text = L"CECI EST UN BUTTON";

	D3DXVECTOR2 position = D3DXVECTOR2(0,0);
	D3DXVECTOR2 size = D3DXVECTOR2(350,75);

	DWORD textFormat = DT_CENTER | DT_VCENTER;

	LPCWSTR boxFilepath = L"Image\\blanc.png";

	FLOAT borderThickness = 5;

	D3DCOLOR normalTextColor = D3DCOLOR_ARGB(255, 0, 0, 0);
	D3DCOLOR disabledTextColor = D3DCOLOR_ARGB(120, 0, 0, 0);

	D3DCOLOR normalBoxColor = D3DCOLOR_ARGB(255, 255 ,255 ,255);
	D3DCOLOR hoverBoxColor = D3DCOLOR_ARGB(255, 204, 204, 204);
	D3DCOLOR clickBoxColor = D3DCOLOR_ARGB(255, 128, 128, 128);
	D3DCOLOR disabledBoxColor = D3DCOLOR_ARGB(120, 128, 128, 128);

	D3DCOLOR normalBorderColor = D3DCOLOR_ARGB(255, 215, 215, 215);
	D3DCOLOR hoverBorderColor = D3DCOLOR_ARGB(255, 164, 164, 164);
	D3DCOLOR clickBorderColor = D3DCOLOR_ARGB(255, 88, 88, 88);
	D3DCOLOR disabledBorderColor = D3DCOLOR_ARGB(120, 128, 128, 128);

	bool drawBox = true;
	bool drawBorder = true;
	bool isDisabled = false;

private:
	string GetType() override { return NAMEOF(Button); }
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void EngineStart() override;
	void EngineUpdate() override;
	void OnClick();
	void Render();
	void OnHover();
	
	bool isAbove();
	bool UpdateMousePos();
	void ColorNormal();
	void ColorDisabled();

	POINT mousePos;

	UINT width;
	UINT height;

	D3DXVECTOR2 rectTopLeft;
	D3DXVECTOR2 rectBottomRight;

	D3DCOLOR textColor;
	D3DCOLOR boxColor;
	D3DCOLOR borderColor;

	ID3DXLine* line = nullptr;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE ppSprite = nullptr;
	RECT textRect;
	ID3DXFont* font = nullptr;
};
