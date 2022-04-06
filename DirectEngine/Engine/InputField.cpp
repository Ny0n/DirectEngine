#include "pch.h"
#include "InputField.h"

void InputField::SetText(wstring string)
{
	_text = string;
	isPlaceholder = false;
	_textColor = normalTextColor;
}

wstring InputField::GetText()
{
	return _text;
}

void InputField::EngineStart()
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

	HR(D3DXCreateSprite(d3ddev, &_sprite))

	HR(D3DXCreateLine(d3ddev, &_pLine))
	HR(_pLine->SetWidth(borderThickness))
	HR(_pLine->SetAntialias(true))
}

void InputField::EngineUpdate()
{
	Render();
	Focus();

	if (_hasFocus)
		EnterFocus();
	else
		ExitFocus();

	if (Input::GetKeyDown(KeyCode::Return) || Input::GetKeyDown(KeyCode::Escape))
	{
		ExitFocus();
		_hasFocus = false;
	}
}

void InputField::Render()
{
	_rectTopLeft = position;
	_rectBottomRight = position + size;

	const auto result = SetRect(&_textRect, _rectTopLeft.x, _rectTopLeft.y, _rectBottomRight.x, _rectBottomRight.y);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	const auto res = SetRect(&_txtRect, _rectTopLeft.x + borderThickness + 5, _rectTopLeft.y, _rectBottomRight.x, _rectBottomRight.y);
	if (res <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	if (drawBox)
	{
		HR(_sprite->Begin(0))

			const auto spritePostion = D3DXVECTOR3(_rectTopLeft.x, _rectTopLeft.y, 0);
		HR(_sprite->Draw(_texture, NULL, NULL, &spritePostion, _boxColor))

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
					D3DXVECTOR2(_rectTopLeft.x - borderThickness * 0.5f,_rectBottomRight.y ),
					D3DXVECTOR2(_rectTopLeft.x,_rectBottomRight.y ),
					D3DXVECTOR2(_rectTopLeft.x,_rectTopLeft.y),
		};

		HR(_pLine->Draw(linesList, 8, _borderColor))

		HR(_pLine->End())

		const int result = _pFont->DrawText(NULL, _text.c_str(), _text.length(), &_txtRect, textFormat, _textColor);
		if (result <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
	}
}

bool InputField::IsAbove()
{
	if(_mousePos.x <= _rectBottomRight.x && _mousePos.x >= _rectTopLeft.x)
	{
		if(_mousePos.y <= _rectBottomRight.y && _mousePos.y >= _rectTopLeft.y)
		{
			return true;
		}
	}
	return false;
}

void InputField::Focus()
{
	if (GetCursorPos(&_mousePos))
	{
		if (ScreenToClient(Engine::GetInstance()->window, &_mousePos))
		{
			if (Input::GetKeyDown(KeyCode::Mouse0))
			{
				if (IsAbove())
					_hasFocus = true;
				else
					_hasFocus = false;
			}
		}
	}
}

void InputField::HandleKeyInput()
{
	bool isLetter = false;
	auto lastKey = Input::GetLastKeyDown();

	if (GetKeyState(VK_CAPITAL) == 1 || Input::GetKey(KeyCode::Shift))
		_maj = true;
	else
		_maj = false;

	if (lastKey != VK_BACK && lastKey != VK_SPACE && lastKey != VK_DELETE)
	{
		if (lastKey >= 65 && lastKey <= 90) // between A and Z
		{
			isLetter = true;
		}
		else if (lastKey >= 48 && lastKey <= 57) { // between 0 and 9
			isLetter = false;
		}
		else
			return;
	}

	switch (lastKey)
	{
		case static_cast<int>(KeyCode::Backspace):
			if (_text.length() > 0)
				_text.pop_back();
			break;
		case static_cast<int>(KeyCode::Delete):
			_text.clear();
			break;
		default:
			if (_text.length() >= textMaxCaracters && textMaxCaracters != 0)
				break;

			if (!_maj && isLetter)
				lastKey += 32;

			const char key = static_cast<char>(lastKey);
			_text += key;
			break;
	}
	
	Input::ResetLastKeyDown();
}

void InputField::EnterFocus()
{
	_borderColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	HandleKeyInput();

	if (togglePlaceholder)
	{
		if (isPlaceholder)
		{
			_text.clear();
			isPlaceholder = false;

			_textColor = normalTextColor;
		}
	}

	_boxColor = focusedBoxColor;
	_borderColor = focusBorderColor;
}

void InputField::ExitFocus()
{
	_borderColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	if (togglePlaceholder)
	{
		if (_text.empty())
		{
			_text = placeholderText;
			isPlaceholder = true;

			_textColor = placeHolderTextColor;
		}
		
	}
	_boxColor = notFocusedBoxColor;
	_borderColor = notFocusBorderColor;
}
