#pragma once

#include "framework.h"
#include "Engine.h"

class App
{

public:
	void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);
	void Loop();
	void Uninit();

private:
	Engine* _engine = nullptr;
	HWND _window = nullptr;

};

