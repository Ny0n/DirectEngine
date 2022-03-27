#include "pch.h"
#include "InputField.h"

void InputField::EngineStart()
{
	counter = counterMaxTime;

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
	if (result <= 0)
		Utils::PrintError(__FILE__, __LINE__, L"SetRect() failed.");

	D3DXIMAGE_INFO info;
	HR(D3DXGetImageInfoFromFile(boxFilepath, &info))

	width = abs(rectTopLeft.x - rectBottomRight.x);
	height = abs(rectTopLeft.y - rectBottomRight.y);

	if (width <= 0 || height <= 0)
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

void InputField::EngineUpdate()
{
	Render();
	if (GetCursorPos(&mousePos))
	{
		if(ScreenToClient(Engine::GetInstance()->window, &mousePos))
		{
			//Utils::Println("x: " + to_string(mousePos.x) + " y: " + to_string(mousePos.y));
			if (isAbove())
			{
				Utils::Println("DING DING DING!!");

				if (Input::GetKeyDown(KeyCode::Mouse0))
					Focus();
			}
		}
	}

	if (counter <= 0)
	{
		HandleKeyInput();
		counter = counterMaxTime;
	}

	counter -= Time::deltaTime;
}

void InputField::Render()
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

		const int result = font->DrawText(NULL, text.c_str(), text.length(), &textRect, textFormat, textColor);
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
	boxColor = D3DCOLOR_ARGB(255, 0, 0, 255);
}

void InputField::HandleKeyInput()
{
	const auto lastKey = Input::GetLastKeyDown();

	switch (lastKey)
	{
		case static_cast<int>(KeyCode::Backspace):
			counterMaxTime = 0.1f;
			if (text.length() > 0)
				text.pop_back();
			break;
		case 0:
			break;
		default:
			counterMaxTime = 0.2f;
			const char key = static_cast<char>(lastKey);
			text += key;
			break;
	}
	
	Input::ResetLastKeyDown();
}
