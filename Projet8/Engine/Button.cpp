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

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void Button::EngineUpdate()
{
	if (UpdateMousePos() == FALSE)
		Utils::PrintError(__FILE__, __LINE__, L"UpdateMouse() failed!");

	Render();

	if (isAbove() && !isDisabled)
	{
		if (Input::GetKey(KeyCode::Mouse0) || Input::GetKeyUp(KeyCode::Mouse0))
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
	rectTopLeft = position;
	rectBottomRight = position + size;

	const auto result = SetRect(&textRect, rectTopLeft.x, rectTopLeft.y, rectBottomRight.x, rectBottomRight.y);
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	if (drawBox)
	{
		HR(ppSprite->Begin(0))

		auto spritePostion = D3DXVECTOR3(rectTopLeft.x, rectTopLeft.y, 0);
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
					D3DXVECTOR2(rectTopLeft.x - borderThickness * 0.5f,rectBottomRight.y),
					D3DXVECTOR2(rectTopLeft.x,rectBottomRight.y),
					D3DXVECTOR2(rectTopLeft.x,rectTopLeft.y),
		};

		HR(line->Draw(linesList, 8, borderColor))

		HR(line->End())

			const int result = font->DrawText(NULL, text.c_str(), text.length(), &textRect, textFormat, textColor);
		if (result <= 0)
			Utils::PrintError(__FILE__, __LINE__, L"DrawText() failed.");
	}
}

void Button::OnHover()
{
	boxColor = hoverBoxColor;
	borderColor = hoverBorderColor;
}

void Button::OnClick()
{
	boxColor = clickBoxColor;
	borderColor = clickBorderColor;

	if (onClick != nullptr && Input::GetKeyUp(KeyCode::Mouse0))
	{
		onClick();
	}
}

bool Button::isAbove()
{
	if (mousePos.x <= rectBottomRight.x && mousePos.x >= rectTopLeft.x)
	{
		if (mousePos.y <= rectBottomRight.y && mousePos.y >= rectTopLeft.y)
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
	boxColor = disabledBoxColor;
	borderColor = disabledBorderColor;
	textColor = disabledTextColor;
}

void Button::ColorNormal()
{
	textColor = normalTextColor;
	boxColor = normalBoxColor;
	borderColor = normalBorderColor;
}


