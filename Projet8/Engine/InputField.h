#pragma once

class InputField : public EngineComponent
{
public:
	void SetText(wstring string);
	wstring GetText();

	INT fontHeight = 25;
	UINT fontWidth = 0;
	UINT fontWeight = FW_NORMAL;
	BOOL fontItalic = false;
	LPCWSTR textFont = L"Arial";

	
	wstring placeholderText = L"Placeholder text...";

	DWORD textFormat = DT_LEFT | DT_VCENTER;

	LPCWSTR boxFilepath = L"Image\\blanc.png";

	D3DXVECTOR2 position = { 100,50 };
	D3DXVECTOR2 size = { 300, 50 };
	
	D3DCOLOR notFocusBorderColor = D3DCOLOR_ARGB(255, 102, 102, 102);
	D3DCOLOR focusBorderColor = D3DCOLOR_ARGB(255, 62, 62, 62);

	D3DCOLOR notFocusedBoxColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DCOLOR focusedBoxColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	D3DCOLOR normalTextColor = D3DCOLOR_ARGB(255, 0, 0, 0);
	D3DCOLOR placeHolderTextColor = D3DCOLOR_ARGB(255, 128, 128, 128);

	FLOAT borderThickness = 5;

	int textMaxCaracters = 0;

	bool drawBox = true;
	bool drawBorder = true;
	bool togglePlaceholder = true;
	bool isPlaceholder = true;

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

	wstring text;

	bool hasFocus = false;
	bool maj;

	D3DXVECTOR2 rectTopLeft;
	D3DXVECTOR2 rectBottomRight;

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

