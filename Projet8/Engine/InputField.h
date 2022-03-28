#pragma once

class InputField : public EngineComponent
{
public:
	INT fontHeight = 25;
	UINT fontWidth = 0;
	UINT fontWeight = FW_NORMAL;
	BOOL fontItalic = false;
	LPCWSTR textFont = L"Arial";

	wstring text;
	wstring placeholderText = L"Placeholder text...";

	DWORD textFormat = DT_LEFT | DT_VCENTER;

	LPCWSTR boxFilepath = L"Image\\blanc.png";

	D3DXVECTOR2 rectTopLeft = { 100,50 };
	D3DXVECTOR2 rectBottomRight = { 400, 100 };

	D3DCOLOR notFocusBorderColor = D3DCOLOR_ARGB(255, 255, 166, 0);
	D3DCOLOR focusBorderColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	D3DCOLOR notFocusedBoxColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DCOLOR focusedBoxColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	D3DCOLOR normalTextColor = D3DCOLOR_ARGB(255, 0, 0, 0);
	D3DCOLOR placeHolderTextColor = D3DCOLOR_ARGB(255, 128, 128, 128);

	FLOAT borderThickness = 5;

	bool drawBox = false;
	bool drawBorder = false;
	bool togglePlaceholder = true;

private:
	string GetType() override { return NAMEOF(InputField); }
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void EngineStart() override;
	void EngineUpdate() override;

	void Render();
	bool isAbove();
	void Focus();
	void HandleKeyInput();
	void EnterFocus();
	void ExitFocus();

	bool hasFocus = false;
	bool isPlaceholder = true;
	bool maj;

	POINT mousePos;

	D3DCOLOR textColor;
	D3DCOLOR boxColor;
	D3DCOLOR borderColor;

	UINT width;
	UINT height;

	ID3DXLine* line = nullptr;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE ppSprite = nullptr;
	RECT textRect;
	RECT txtRect;
	ID3DXFont* font = nullptr;
};

