#pragma once

class InputField : public EngineComponent
{
	string GetType() override { return NAMEOF(InputField); }
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void EngineStart() override;
	void EngineUpdate() override
	;
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
	void Render();
	bool IsAbove();
	void Focus();
	void HandleKeyInput();
	void EnterFocus();
	void ExitFocus();

	wstring _text;

	bool _hasFocus = false;
	bool _maj;

	D3DXVECTOR2 _rectTopLeft;
	D3DXVECTOR2 _rectBottomRight;

	POINT _mousePos;

	D3DCOLOR _textColor;
	D3DCOLOR _boxColor;
	D3DCOLOR _borderColor;
	
	ID3DXLine* _pLine = nullptr;
	LPDIRECT3DTEXTURE9 _texture;
	LPD3DXSPRITE _sprite = nullptr;
	RECT _textRect;
	RECT _txtRect;
	ID3DXFont* _pFont = nullptr;
};

