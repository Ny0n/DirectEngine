// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Windows Header Files
#include <windows.h>
#include <windowsx.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>

#include <d3d9.h>
#include <d3dx9.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "winmm.lib")
# pragma comment(lib, "dmoguids.lib")
# pragma comment(lib, "wmcodecdspuuid.lib")
# pragma comment(lib, "msdmo.lib")
# pragma comment(lib, "Strmiids.lib")
# pragma comment(lib, "Kernel32.lib")

// declare global variables
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

extern LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
extern LPDIRECT3DVERTEXBUFFER9 _VBuffer;    // the pointer to the vertex buffer
extern LPDIRECT3DINDEXBUFFER9 _IBuffer;    // the pointer to the index buffer

//structure
struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

using namespace std;
