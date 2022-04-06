#include "App.h"

#include "GameScene.h"
#include "MenuScene.h"

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
        L"Mine",   // title of the window
        WS_EX_TOPMOST | WS_POPUP,    // window style WS_EX_TOPMOST | WS_POPUP
        0,    // x-position of the window
        0,    // y-position of the window
        SCREEN_WIDTH,    // width of the window
        SCREEN_HEIGHT,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(_window, nCmdShow);
}

void App::Run()
{
    // first we prep the scenes that will be used in the app
    SceneManager::AddToBuild(new MenuScene());
    SceneManager::AddToBuild(new GameScene());
	
    // and then we run the game
    Engine::GetInstance()->Run(_window);
}

void App::Uninit() const
{
}
