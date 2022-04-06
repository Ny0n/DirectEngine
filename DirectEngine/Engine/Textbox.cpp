#include "pch.h"
#include "Textbox.h"

Textbox::Textbox()
{
}

Textbox::~Textbox()
{
	_pFont->Release();
	_sprite->Release();
	_pLine->Release();
}

void Textbox::EngineStart()
{
	HR(D3DXCreateFont(d3ddev,
		fontHeight,
		fontWidth,
		fontWeight,
		D3DX_DEFAULT,
		fontItalic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		textFont,
		&_pFont))


	D3DXIMAGE_INFO info;
	HR(D3DXGetImageInfoFromFile(boxFilepath, &info))

	if(size.x <= 0 || size.y <= 0 )
	{
		drawBox = false;
	}

	HR(D3DXCreateTextureFromFileEx(d3ddev,
		boxFilepath,
		size.x,
		size.y,
		info.MipLevels,
		0,
		info.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
		&info,
		NULL,
		&_texture))

	HR(D3DXCreateSprite(d3ddev, &_sprite))

	HR(D3DXCreateLine(d3ddev, &_pLine))
	HR(_pLine->SetWidth(borderThickness))
	HR(_pLine->SetAntialias(true))
}

void Textbox::EngineUpdate()
{
	Render();
}

void Textbox::Render()
{
	_rectTopLeft = position;
	_rectBottomRight = position + size;

	const auto res = SetRect(&_textRect, _rectTopLeft.x, _rectTopLeft.y, _rectBottomRight.x, _rectBottomRight.y);
	if (res <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	if (drawBox)
	{
		HR(_sprite->Begin(D3DXSPRITE_ALPHABLEND))

		const auto spritePostion = D3DXVECTOR3(_rectTopLeft.x, _rectTopLeft.y, 0);
		HR(_sprite->Draw(_texture, NULL, NULL, &spritePostion, boxColor))

		HR(_sprite->End())
	}

	if (drawBorder)
	{
		HR(_pLine->Begin())

		D3DXVECTOR2 linesList[] = {
			D3DXVECTOR2(_rectTopLeft.x - borderThickness * 0.5f,_rectTopLeft.y),
			D3DXVECTOR2(_rectBottomRight.x + borderThickness * 0.5f,_rectTopLeft.y),
			D3DXVECTOR2(_rectBottomRight.x,_rectTopLeft.y),
			D3DXVECTOR2(_rectBottomRight.x,_rectBottomRight.y),
			D3DXVECTOR2(_rectBottomRight.x + borderThickness * 0.5f,_rectBottomRight.y),
			D3DXVECTOR2(_rectTopLeft.x - borderThickness * 0.5f,_rectBottomRight.y),
			D3DXVECTOR2(_rectTopLeft.x,_rectBottomRight.y),
			D3DXVECTOR2(_rectTopLeft.x,_rectTopLeft.y),
		};

		HR(_pLine->Draw(linesList, 8, borderColor))

		HR(_pLine->End())
	}
	
	const int result = _pFont->DrawText(NULL, text.c_str(), text.length(), &_textRect, textFormat, textColor);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
}
