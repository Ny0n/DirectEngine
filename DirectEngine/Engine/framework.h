// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Windows Header Files
#include <Windows.h>
#include <windowsx.h>

// C RunTime Header Files
#include <cstdlib>
#include <map>
#include <functional>
#include <typeinfo>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <algorithm>
#include <timeapi.h>
#include <profileapi.h>
#include <cstring>
#include <sstream>
#include <chrono>
#include <thread>
#include <utility>

#include <d3d9.h>
#include <d3dx9.h>

#include <X3DAudio.h>
#include <XAudio2.h>
#include <XAudio2fx.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "X3DAudio.lib")
#pragma comment (lib, "dsound.lib")

#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "msdmo.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Kernel32.lib")

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <DxErr.h>

// **************************** //

using namespace std;

// #DEFINE DelegateToolBox

#define DELEGATE(exp) [=] { exp } // TODO pas =, mais du coup refaire dans gamescene le SUPPLIER, en fait faudrait faire une func ou jsais pas, parceque la ref est pas la meme

#define Runner std::function<void()>
#define RUNNER(func) DELEGATE(func();)
#define Consumer(T) std::function<void(T)>
#define Mixer(T) std::function<void((T)...)>

#define Supplier(TResult) std::function<TResult()>
#define SUPPLIER(data) DELEGATE(return data;)
#define Producer(T, TResult) std::function<TResult(T)>
#define Merger(T, TResult) std::function<TResult((T)...)>

#define Predicate(T) std::function<bool(T)>

// #DEFINE

// gives the pure name of a class
#define CLASSNAMEOF(T) string(typeid(T).name()).substr(6)
// gives the type name of a var / class
#define NAMEOF(T) string(typeid(T).name())

#define HR(x)										\
{													\
	HRESULT hr = x;									\
	if (FAILED(hr))									\
	{												\
		DXTraceA(__FILE__, __LINE__, hr, #x, FALSE);\
	}												\
}

// application
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

// GLOBAL VARIABLES

//directx
extern LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

//structure
struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)
