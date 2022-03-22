#pragma once

class Canvas : public EngineComponent
{

public:
	const char* GetType() override { return NAMEOF(Canvas); }

	void EngineStart() override;
	void EngineUpdate() override;

protected:
	virtual void Render();

	bool isVisible = true;
	int layerOrder = 0;

	DWORD width = 800;
	DWORD heigth = 600;
};

