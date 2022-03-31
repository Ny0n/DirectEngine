#include "pch.h"

Button::Button()
{
}

Button::~Button()
{
}

// **************************** //

// EngineStart is called once, before the MonoBehaviour Start
void Button::EngineStart()
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
		
	if (size.x <= 0 || size.y <= 0)
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

	HR(D3DXCreateSprite(d3ddev, &_ppSprite))
	HR(D3DXCreateLine(d3ddev, &_pLine))
	HR(_pLine->SetWidth(borderThickness))
	HR(_pLine->SetAntialias(true))
}

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void Button::EngineUpdate()
{
	if (UpdateMousePos() == FALSE)
		Utils::PrintError(__FILE__, __LINE__, L"UpdateMouse() failed!");

	Render();

	if (isAbove() && !isDisabled)
	{
		if (Input::GetKeyDown(KeyCode::Mouse0) || Input::GetKeyUp(KeyCode::Mouse0))
			OnClick();
		else
			OnHover();
	}
	else if (!isAbove() && !isDisabled)
		ColorNormal();
	else
		ColorDisabled();
}

void Button::Render()
{
	_rectTopLeft = position;
	_rectBottomRight = position + size;

	const auto result = SetRect(&_textRect, _rectTopLeft.x, _rectTopLeft.y, _rectBottomRight.x, _rectBottomRight.y);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	if (drawBox)
	{
		HR(_ppSprite->Begin(D3DXSPRITE_ALPHABLEND))

		auto spritePostion = D3DXVECTOR3(_rectTopLeft.x, _rectTopLeft.y, 0);
		HR(_ppSprite->Draw(_texture, NULL, NULL, &spritePostion, _boxColor))

		HR(_ppSprite->End())
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

		HR(_pLine->Draw(linesList, 8, _borderColor))

		HR(_pLine->End())
	}

	const int res = _pFont->DrawText(NULL, text.c_str(), text.length(), &_textRect, textFormat, _textColor);
	if (res <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
}

void Button::OnHover()
{
	_boxColor = hoverBoxColor;
	_borderColor = hoverBorderColor;
}

void Button::OnClick()
{
	_boxColor = clickBoxColor;
	_borderColor = clickBorderColor;

	if (onClick != nullptr && Input::GetKeyUp(KeyCode::Mouse0))
	{
		onClick();
	}
}

bool Button::isAbove()
{
	if (mousePos.x <= _rectBottomRight.x && mousePos.x >= _rectTopLeft.x)
	{
		if (mousePos.y <= _rectBottomRight.y && mousePos.y >= _rectTopLeft.y)
		{
			return true;
		}
	}
	return false;
}

bool Button::UpdateMousePos()
{
	if (GetCursorPos(&mousePos))
	{
		if (ScreenToClient(Engine::GetInstance()->window, &mousePos))
		{
			return true;
		}
	}

	return false;
}

void Button::ColorDisabled()
{
	_boxColor = disabledBoxColor;
	_borderColor = disabledBorderColor;
	_textColor = disabledTextColor;
}

void Button::ColorNormal()
{
	_textColor = normalTextColor;
	_boxColor = normalBoxColor;
	_borderColor = normalBorderColor;
}


