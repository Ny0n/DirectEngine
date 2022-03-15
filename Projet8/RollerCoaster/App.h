#pragma once

#include "EngineLib.h"

class App
{

public:
	void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);
	void Loop();
	void Uninit() const;

private:
	Engine* _engine = nullptr;
	HWND _window = nullptr;

};
