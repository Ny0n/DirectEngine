#pragma once

class Textbox final : public EngineComponent
{
	void EngineStart() override;
	void EngineUpdate() override;

public:
	string GetType() override { return NAMEOF(Textbox); }

	explicit Textbox(LPCWSTR text);
	~Textbox() override;

	INT fontHeight = 25;
	UINT fontWidth = 0;
	UINT fontWeight = FW_NORMAL;
	BOOL fontItalic = false;
	LPCWSTR text = L"Default string!";
	DWORD textFormat = DT_LEFT;
	RECT textRect;
	D3DCOLOR textColor = D3DCOLOR_ARGB(255, 255, 255, 0);

private:
	void Render();

	ID3DXFont* font = nullptr;

};

