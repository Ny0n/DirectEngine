#include "pch.h"
#include "InputField.h"

void InputField::SetText(wstring string)
{
	text = string;
	isPlaceholder = false;
	textColor = normalTextColor;
}

wstring InputField::GetText()
{
	return text;
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
		&font))
	
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
		&texture))

	HR(D3DXCreateSprite(d3ddev, &ppSprite))

	HR(D3DXCreateLine(d3ddev, &line))
	HR(line->SetWidth(borderThickness))
	HR(line->SetAntialias(true))
}

void InputField::EngineUpdate()
{
	Render();
	Focus();

	if (hasFocus)
		EnterFocus();
	else
		ExitFocus();

	if (Input::GetKeyDown(KeyCode::Return) || Input::GetKeyDown(KeyCode::Escape))
	{
		ExitFocus();
		hasFocus = false;
	}
}

void InputField::Render()
{
	rectTopLeft = position;
	rectBottomRight = position + size;

	const auto result = SetRect(&textRect, rectTopLeft.x, rectTopLeft.y, rectBottomRight.x, rectBottomRight.y);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	const auto res = SetRect(&txtRect, rectTopLeft.x + borderThickness + 5, rectTopLeft.y, rectBottomRight.x, rectBottomRight.y);
	if (res <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

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
					D3DXVECTOR2(rectTopLeft.x - borderThickness * 0.5f,rectTopLeft.y),
					D3DXVECTOR2(rectBottomRight.x + borderThickness * 0.5f,rectTopLeft.y),
					D3DXVECTOR2(rectBottomRight.x,rectTopLeft.y),
					D3DXVECTOR2(rectBottomRight.x,rectBottomRight.y),
					D3DXVECTOR2(rectBottomRight.x + borderThickness * 0.5f,rectBottomRight.y),
					D3DXVECTOR2(rectTopLeft.x - borderThickness * 0.5f,rectBottomRight.y ),
					D3DXVECTOR2(rectTopLeft.x,rectBottomRight.y ),
					D3DXVECTOR2(rectTopLeft.x,rectTopLeft.y),
		};

		HR(line->Draw(linesList, 8, borderColor))

		HR(line->End())

		const int result = font->DrawText(NULL, text.c_str(), text.length(), &txtRect, textFormat, textColor);
		if (result <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
	}
}

bool InputField::isAbove()
{
	if(mousePos.x <= rectBottomRight.x && mousePos.x >= rectTopLeft.x)
	{
		if(mousePos.y <= rectBottomRight.y && mousePos.y >= rectTopLeft.y)
		{
			return true;
		}
	}
	return false;
}

void InputField::Focus()
{
	if (GetCursorPos(&mousePos))
	{
		if (ScreenToClient(Engine::GetInstance()->window, &mousePos))
		{
			if (Input::GetKeyDown(KeyCode::Mouse0))
			{
				if (isAbove())
					hasFocus = true;
				else
					hasFocus = false;
			}
		}
	}
}

void InputField::HandleKeyInput()
{
	bool isLetter = false;
	auto lastKey = Input::GetLastKeyDown();

	if (GetKeyState(VK_CAPITAL) == 1 || Input::GetKey(KeyCode::Shift))
		maj = true;
	else
		maj = false;

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
			if (text.length() > 0)
				text.pop_back();
			break;
		case static_cast<int>(KeyCode::Delete):
			text.clear();
			break;
		default:
			if (text.length() >= textMaxCaracters && textMaxCaracters != 0)
				break;

			if (!maj && isLetter)
				lastKey += 32;

			const char key = static_cast<char>(lastKey);
			text += key;
			break;
	}
	
	Input::ResetLastKeyDown();
}

void InputField::EnterFocus()
{
	borderColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	HandleKeyInput();

	if (togglePlaceholder)
	{
		if (isPlaceholder)
		{
			text.clear();
			isPlaceholder = false;

			textColor = normalTextColor;
		}
	}

	boxColor = focusedBoxColor;
	borderColor = focusBorderColor;
}

void InputField::ExitFocus()
{
	borderColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	if (togglePlaceholder)
	{
		if (text.empty())
		{
			text = placeholderText;
			isPlaceholder = true;

			textColor = placeHolderTextColor;
		}
		
	}
	boxColor = notFocusedBoxColor;
	borderColor = notFocusBorderColor;
}
