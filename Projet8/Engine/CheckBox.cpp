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

	boxColor = checkedBoxColor;
	borderColor = checkedBorderColor;
	textColor = checkedTextColor;
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
		&font))

	D3DXIMAGE_INFO info;
	HR(D3DXGetImageInfoFromFile(boxFilepath, &info))


	if (size.x <= 0 || size.y <= 0)
	{
		_drawBox = false;
	}

	HR(D3DXCreateSprite(d3ddev, &ppSprite))
	HR(D3DXCreateLine(d3ddev, &line))
	HR(line->SetWidth(borderThickness))
	HR(line->SetAntialias(true))

	HR(D3DXGetImageInfoFromFile(boxFilepath, &info))
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

	D3DXIMAGE_INFO infoChecked;
	HR(D3DXGetImageInfoFromFile(boxFilepath, &infoChecked))
	HR(D3DXGetImageInfoFromFile(checkedBoxFilepath, &infoChecked))
	HR(D3DXCreateTextureFromFileEx(d3ddev,
		checkedBoxFilepath,
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
		&textureChecked))
}

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void CheckBox::EngineUpdate()
{
	if (UpdateMousePos() == FALSE)
		Utils::PrintError(__FILE__, __LINE__, L"UpdateMouse() failed!");

	Render();

	if (isAbove() && !isDisabled)
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
	if (GetCursorPos(&mousePos))
	{
		if (ScreenToClient(Engine::GetInstance()->window, &mousePos))
		{
			return true;
		}
	}

	return false;
}

void CheckBox::Render()
{
	rectTopLeft = position;
	rectBottomRight = position + size;
		
	const auto result = SetRect(&textRect, rectTopLeft.x, rectTopLeft.y, rectBottomRight.x, rectBottomRight.y);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	if (_drawBox)
	{
		HR(ppSprite->Begin(D3DXSPRITE_ALPHABLEND))

		auto spritePostion = D3DXVECTOR3(rectTopLeft.x, rectTopLeft.y, 0);

		if (drawBackground)
			HR(ppSprite->Draw(texture, NULL, NULL, &spritePostion, backgroundBoxColor))

		if (_checked)
		{
			HR(ppSprite->Draw(textureChecked, NULL, NULL, &spritePostion, boxColor))
		}
		else
		{
			ColorNormal();
		}

		HR(ppSprite->End())

		HR(line->Begin())

		D3DXVECTOR2 linesList[] = {
			D3DXVECTOR2(rectTopLeft.x - borderThickness * 0.5f, rectTopLeft.y),
			D3DXVECTOR2(rectBottomRight.x + borderThickness * 0.5f, rectTopLeft.y),
			D3DXVECTOR2(rectBottomRight.x, rectTopLeft.y),
			D3DXVECTOR2(rectBottomRight.x, rectBottomRight.y),
			D3DXVECTOR2(rectBottomRight.x + borderThickness * 0.5f, rectBottomRight.y),
			D3DXVECTOR2(rectTopLeft.x - borderThickness * 0.5f, rectBottomRight.y),
			D3DXVECTOR2(rectTopLeft.x, rectBottomRight.y),
			D3DXVECTOR2(rectTopLeft.x, rectTopLeft.y),
		};

		HR(line->Draw(linesList, 8, borderColor))

		HR(line->End())
	}

	if (drawText)
	{
		const auto res = SetRect(&textPos, rectTopLeft.x + size.x + borderThickness + 5, rectTopLeft.y, rectBottomRight.x + textBoxWidth, rectBottomRight.y);
		if (res <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

		const int result = font->DrawText(NULL, text.c_str(), text.length(), &textPos, textFormat, textColor);
		if (result <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
	}
}

bool CheckBox::isAbove()
{
	if (mousePos.x <= textPos.right && mousePos.x >= rectTopLeft.x)
	{
		if (mousePos.y <= textPos.bottom && mousePos.y >= rectTopLeft.y)
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

	boxColor = checkedBoxColor;
	borderColor = checkedBorderColor;
	textColor = checkedTextColor;

	if (onClick != nullptr && Input::GetKeyUp(KeyCode::Mouse0))
	{
		onClick();
	}
}

void CheckBox::ColorNormal()
{
	textColor = normalTextColor;
	boxColor = normalBoxColor;
	borderColor = normalBorderColor;
}

void CheckBox::ColorDisabled()
{
	boxColor = disabledBoxColor;
	borderColor = disabledBorderColor;
	textColor = disabledTextColor;
}
