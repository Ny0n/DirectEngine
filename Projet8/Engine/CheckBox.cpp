#include "pch.h"
#include "CheckBox.h" // MOVE THIS LINE IN EngineLib.h

CheckBox::CheckBox()
{
}

CheckBox::~CheckBox()
{
}

bool CheckBox::IsChecked() const
{
	return _checked;
}

void CheckBox::SetCheck(bool b)
{
	_checked = b;

	_boxColor = checkedBoxColor;
	_borderColor = checkedBorderColor;
	_textColor = checkedTextColor;
}

// **************************** //

// EngineStart is called once, before the MonoBehaviour Start
void CheckBox::EngineStart()
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
	HR(D3DXGetImageInfoFromFile(_boxFilepath, &info))


	if (size.x <= 0 || size.y <= 0)
	{
		_drawBox = false;
	}

	HR(D3DXCreateSprite(d3ddev, &_sprite))
	HR(D3DXCreateLine(d3ddev, &_pLine))
	HR(_pLine->SetWidth(borderThickness))
	HR(_pLine->SetAntialias(true))

	HR(D3DXGetImageInfoFromFile(_boxFilepath, &info))
	HR(D3DXCreateTextureFromFileEx(d3ddev,
		_boxFilepath,
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

	D3DXIMAGE_INFO infoChecked;
	HR(D3DXGetImageInfoFromFile(_boxFilepath, &infoChecked))
	HR(D3DXGetImageInfoFromFile(_checkedBoxFilepath, &infoChecked))
	HR(D3DXCreateTextureFromFileEx(d3ddev,
		_checkedBoxFilepath,
		size.x,
		size.y,
		infoChecked.MipLevels,
		0,
		infoChecked.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
		&infoChecked,
		NULL,
		&_textureChecked))
}

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void CheckBox::EngineUpdate()
{
	if (UpdateMousePos() == FALSE)
		Utils::PrintError(__FILE__, __LINE__, L"UpdateMouse() failed!");

	Render();

	if (IsAbove() && !isDisabled)
	{
		if (Input::GetKeyUp(KeyCode::Mouse0))
			OnClick();
	}
	else if (!_checked && !isDisabled)
		ColorNormal();
	else if (isDisabled)
		ColorDisabled();
}

bool CheckBox::UpdateMousePos()
{
	if (GetCursorPos(&_mousePos))
	{
		if (ScreenToClient(Engine::GetInstance()->window, &_mousePos))
		{
			return true;
		}
	}

	return false;
}

void CheckBox::Render()
{
	_rectTopLeft = position;
	_rectBottomRight = position + size;
		
	const auto result = SetRect(&_textRect, _rectTopLeft.x, _rectTopLeft.y, _rectBottomRight.x, _rectBottomRight.y);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	if (_drawBox)
	{
		HR(_sprite->Begin(D3DXSPRITE_ALPHABLEND))

		auto spritePostion = D3DXVECTOR3(_rectTopLeft.x, _rectTopLeft.y, 0);

		if (drawBackground)
			HR(_sprite->Draw(_texture, NULL, NULL, &spritePostion, backgroundBoxColor))

		if (_checked)
		{
			HR(_sprite->Draw(_textureChecked, NULL, NULL, &spritePostion, _boxColor))
		}
		else
		{
			ColorNormal();
		}

		HR(_sprite->End())

		HR(_pLine->Begin())

		D3DXVECTOR2 linesList[] = {
			D3DXVECTOR2(_rectTopLeft.x - borderThickness * 0.5f, _rectTopLeft.y),
			D3DXVECTOR2(_rectBottomRight.x + borderThickness * 0.5f, _rectTopLeft.y),
			D3DXVECTOR2(_rectBottomRight.x, _rectTopLeft.y),
			D3DXVECTOR2(_rectBottomRight.x, _rectBottomRight.y),
			D3DXVECTOR2(_rectBottomRight.x + borderThickness * 0.5f, _rectBottomRight.y),
			D3DXVECTOR2(_rectTopLeft.x - borderThickness * 0.5f, _rectBottomRight.y),
			D3DXVECTOR2(_rectTopLeft.x, _rectBottomRight.y),
			D3DXVECTOR2(_rectTopLeft.x, _rectTopLeft.y),
		};

		HR(_pLine->Draw(linesList, 8, _borderColor))

		HR(_pLine->End())
	}

	if (drawText)
	{
		const auto res = SetRect(&_textPos, _rectTopLeft.x + size.x + borderThickness + 5, _rectTopLeft.y, _rectBottomRight.x + textBoxWidth, _rectBottomRight.y);
		if (res <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

		const int result = _pFont->DrawText(NULL, text.c_str(), text.length(), &_textPos, textFormat, _textColor);
		if (result <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
	}
}

bool CheckBox::IsAbove()
{
	if (_mousePos.x <= _textPos.right && _mousePos.x >= _rectTopLeft.x)
	{
		if (_mousePos.y <= _textPos.bottom && _mousePos.y >= _rectTopLeft.y)
		{
			return true;
		}
	}
	return false;
}

void CheckBox::OnClick()
{
	if (!_checked)
		_checked = true;
	else
		_checked = false;

	_boxColor = checkedBoxColor;
	_borderColor = checkedBorderColor;
	_textColor = checkedTextColor;

	if (onClick != nullptr && Input::GetKeyUp(KeyCode::Mouse0))
	{
		onClick();
	}
}

void CheckBox::ColorNormal()
{
	_textColor = normalTextColor;
	_boxColor = normalBoxColor;
	_borderColor = normalBorderColor;
}

void CheckBox::ColorDisabled()
{
	_boxColor = disabledBoxColor;
	_borderColor = disabledBorderColor;
	_textColor = disabledTextColor;
}
