#pragma once

#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
	#pragma comment(lib, "d3dx9d.lib")
#else
	#pragma comment(lib, "d3dx9.lib")
#endif // _DEBUG

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// 3D
#include <d3dx9.h>

 // Windows
#include <windows.h>

// C Runtime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <math.h>

//test enculé