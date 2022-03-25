#pragma once

#include "EngineLib.h"

class App
{

public:
	void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);
	void Run();
	void Uninit() const;
	
private:
	HWND _window = nullptr;

};
