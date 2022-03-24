#include "pch.h"
#include "Textbox.h"

Textbox::Textbox(LPCWSTR text) : string(text)
{
}

Textbox::~Textbox()
{
	font->Release();
}

void Textbox::EngineStart()
{
	D3DXCreateFont(d3ddev,
		fontHeight,
		fontWidth,
		fontWeight,
		D3DX_DEFAULT,
		fontItalic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		L"Arial",
		&font);

	SetRect(&textRect, 100, 0, 200, 200);
}

void Textbox::EngineUpdate()
{
	Render();
}

void Textbox::Render()
{
	font->DrawText(NULL, string, wcslen(string), &textRect, textFormat, textColor);
}
