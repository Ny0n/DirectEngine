﻿#pragma once

class CheckBox : public EngineComponent
{
	string GetType() override { return NAMEOF(CheckBox); }
	ComponentCategory GetCategory() override { return ComponentCategory::multiple; }

	void EngineStart() override;
	void EngineUpdate() override;

public:
	CheckBox();
	~CheckBox() override;
	bool IsChecked() const;
	void SetCheck(bool b);

	function<void()> onClick = nullptr;
	
	INT fontHeight = 15;
	UINT fontWidth = 0;
	UINT fontWeight = FW_NORMAL;
	BOOL fontItalic = false;
	LPCWSTR textFont = L"Arial";
	wstring text = L"JE SUIS UNE CHECKBOX";
	int textBoxWidth = 150;

	D3DXVECTOR2 position = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 size = D3DXVECTOR2(25, 25);

	DWORD textFormat = DT_LEFT | DT_VCENTER;

	FLOAT borderThickness = 3;

	D3DCOLOR normalTextColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DCOLOR checkedTextColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DCOLOR disabledTextColor = D3DCOLOR_ARGB(120, 255, 255, 255);

	D3DCOLOR normalBoxColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DCOLOR checkedBoxColor = D3DCOLOR_ARGB(255, 64, 191, 64);
	D3DCOLOR disabledBoxColor = D3DCOLOR_ARGB(255, 128, 128, 128);
	D3DCOLOR backgroundBoxColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	D3DCOLOR normalBorderColor = D3DCOLOR_ARGB(255, 102, 102, 102);
	D3DCOLOR checkedBorderColor = D3DCOLOR_ARGB(255, 62, 62, 62);
	D3DCOLOR disabledBorderColor = D3DCOLOR_ARGB(255, 102, 102, 102);

	bool drawText = true;
	bool drawBackground = true;
	bool isDisabled = false;
private:
	bool UpdateMousePos();
	void Render();
	bool IsAbove();
	void OnClick();
	void ColorNormal();
	void ColorDisabled();

	LPCWSTR _boxFilepath = L"Image\\blanc.png";
	LPCWSTR _checkedBoxFilepath = L"Image\\checked.png";

	bool _checked = false;
	bool _drawBox = true;

	POINT _mousePos;

	UINT _width;
	UINT _height;

	D3DXVECTOR2 _rectTopLeft;
	D3DXVECTOR2 _rectBottomRight;

	D3DCOLOR _textColor;
	D3DCOLOR _boxColor;
	D3DCOLOR _borderColor;

	ID3DXLine* _pLine = nullptr;
	LPDIRECT3DTEXTURE9 _texture;
	LPDIRECT3DTEXTURE9 _textureChecked;
	LPD3DXSPRITE _sprite = nullptr;
	RECT _textRect;
	RECT _textPos;
	ID3DXFont* _pFont = nullptr;
};
