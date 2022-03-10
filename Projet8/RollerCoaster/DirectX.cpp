
#include "framework.h"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <type_traits>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

// ************/ Global declarations /************ //

constexpr int TARGET_FPS = 60;

LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

// ************/ Prototypes /************ //

void mainLoop(HWND& hWnd, MSG& msg);
void update(float runTime, float deltaTime);

void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(float timeSinceStart, float elapsed);    // renders a single frame
void cleanD3D();    // closes Direct3D and releases memory

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // the WindowProc function prototype

// ************/ Utils /************ //

void println(string s)
{
    s += "\n";
    wstring temp(s.begin(), s.end());
    LPCWSTR lpcwstr = temp.c_str();
    OutputDebugStringW(lpcwstr);
}

long long getStartTime()
{
    long long currentMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return currentMs;
}

float getTimeSinceStart(const long long startTime)
{
    long long currentMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    currentMs -= startTime;
    return currentMs / 1000.0f;
}

// ************/ Windows /************ //

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ** creating the windows class

    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    // register the window class
    RegisterClassEx(&wc);

    // ** creating the window

    // the handle for the window, filled by a function
    HWND hWnd;

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
        L"WindowClass1",    // name of the window class
        L"Our First Direct3D Program",   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        300,    // x-position of the window
        300,    // y-position of the window
        800,    // width of the window
        600,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        NULL);    // used with multiple windows, NULL

	// display the window on the screen
    ShowWindow(hWnd, nCmdShow);

    // ** entering the main loop:

    // this struct holds Windows event messages
    MSG msg;

    mainLoop(hWnd, msg);

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
        // this message is read when the window is closed
	    case WM_DESTROY:
	    {
	        // close the application entirely
	        PostQuitMessage(0);
	        return 0;
	    } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void mainLoop(HWND& hWnd, MSG& msg)
{
	const float frameRate = 1.0f / TARGET_FPS;

    long long start = getStartTime();
    float last = 0.0f;
    float current, elapsed;

    // set up and initialize Direct3D
    initD3D(hWnd);

    // Enter the infinite message loop
    while (TRUE)
    {
        // Check to see if any messages are waiting in the queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // If the message is WM_QUIT, exit the while loop
        if (msg.message == WM_QUIT)
            break;

        // Run game code here

        current = getTimeSinceStart(start);
        elapsed = current - last;

        if (elapsed >= frameRate)
        {
            render_frame(current, elapsed);
            last = current;
        }
    }

    // clean up DirectX and COM
    cleanD3D();
}

// ************/ DirectX /************ //

// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);
}

// this is the function used to render a single frame
void render_frame(float timeSinceStart, float elapsed)
{
    // clear the window to a deep blue
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

    d3ddev->BeginScene();    // begins the 3D scene

    update(timeSinceStart, elapsed);

    d3ddev->EndScene();    // ends the 3D scene

    d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}

// this is the function that cleans up Direct3D and COM
void cleanD3D()
{
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}

// ************/ Game /************ //

void update(float runTime, float deltaTime)
{
    stringstream ss;
    ss << "runTime: " << to_string(runTime) << " deltaTime: " << to_string(deltaTime);
    string s = ss.str();
    println(s);
}
