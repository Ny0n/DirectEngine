#include "App.h"

#include "DefaultScene.h"

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

void App::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
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
    wc.lpszClassName = L"WindowClass";

    // register the window class
    RegisterClassEx(&wc);

    // ** creating the window

    // create the window and use the result as the handle
    _window = CreateWindowEx(NULL,
        L"WindowClass",    // name of the window class
        L"Our First Direct3D Program",   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        0,    // x-position of the window
        0,    // y-position of the window
        720,    // width of the window
        480,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(_window, nCmdShow);
}

void App::Run()
{
    SceneManager::LoadScene(new DefaultScene());
    Engine::GetInstance()->Run(_window);
}

void App::Uninit() const
{
}
