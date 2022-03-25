#include "pch.h"
#include "Textbox.h"

Textbox::Textbox()
{
}

Textbox::~Textbox()
{
	font->Release();
	texture->Release();
	ppSprite->Release();
	line->Release();
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
		&font))

	const auto result = SetRect(&textRect, rectTopLeft.x, rectTopLeft.y, rectBottomRight.x, rectBottomRight.y);
	if (result != 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	D3DXIMAGE_INFO info;
	HR(D3DXGetImageInfoFromFile(boxFilepath, &info))

	width = abs(rectTopLeft.x - rectBottomRight.x);
	height = abs(rectTopLeft.y - rectBottomRight.y);

	if(width <= 0 || height <= 0 )
	{
		drawBox = false;
	}

	HR(D3DXCreateTextureFromFileEx(d3ddev,
		boxFilepath,
		width,
		height,
		info.MipLevels,
		0,
		info.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
		&info,
		NULL,
		&texture))

	HR(D3DXCreateSprite(d3ddev, &ppSprite))

	HR(D3DXCreateLine(d3ddev, &line))
	HR(line->SetWidth(borderThickness))
	HR(line->SetAntialias(true))
}

void Textbox::EngineUpdate()
{
	Render();
}

void Textbox::Render()
{

	if (drawBox)
	{
		HR(ppSprite->Begin(0))

		const auto spritePostion = D3DXVECTOR3(rectTopLeft.x, rectTopLeft.y, 0);
		HR(ppSprite->Draw(texture, NULL, NULL, &spritePostion, boxColor))

		HR(ppSprite->End())
	}

	if (drawBorder)
	{
		HR(line->Begin())

		D3DXVECTOR2 linesList[] = {
				D3DXVECTOR2(rectTopLeft.x,rectTopLeft.y),
				D3DXVECTOR2(rectBottomRight.x,rectTopLeft.y),
				D3DXVECTOR2(rectBottomRight.x,rectBottomRight.y),
				D3DXVECTOR2(rectTopLeft.x,rectBottomRight.y),
				D3DXVECTOR2(rectTopLeft.x,rectTopLeft.y),
		};

		HR(line->Draw(linesList, 5, borderColor))

		HR(line->End())
	}
	
	const int result = font->DrawText(NULL, text.c_str(), text.length(), &textRect, textFormat, textColor);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
}
