#include "pch.h"

// **************************** //

LPDIRECT3D9 d3d; // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev; // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 _VBuffer = nullptr;
LPDIRECT3DINDEXBUFFER9 _IBuffer = nullptr;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    D3DXVECTOR3 Pos;
    D3DXVECTOR3 Normal;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                   g_hInst = NULL;
HWND                        g_hWnd = NULL;
D3DXMATRIX                  g_World;
D3DXMATRIX                  g_View;
D3DXMATRIX                  g_Projection;

// **************************** //

Engine* Engine::instance = nullptr;

Engine::Engine() : window(_window), _profiler(new Profiler())
{
    Time::_profiler = _profiler;
}

Engine::~Engine()
{
    delete(_profiler);
    instance = nullptr;
}


void Engine::InitD3D()
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = _window;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        _window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);

    //
    d3ddev->SetRenderState(D3DRS_LIGHTING, true);    // turn on the 3D lighting
    // d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(250, 250,210 ));    // ambient light

    // d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    float Start = 60.0f,    // Linear fog distances
        End = 100.0f;

    // Enable fog blending.
    d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE);

    // Set the fog color.
    d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_XRGB(0, 0, 0));

    d3ddev->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
    d3ddev->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
        d3ddev->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));

    // _VBuffer
    d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &_VBuffer,
        NULL);

    // _IBuffer
    d3ddev->CreateIndexBuffer(36 * sizeof(short),
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &_IBuffer,
        NULL);

 //   // Create the effect
 //   ID3DXEffect* g_pEffect = NULL;

 //   DWORD dwShaderFlags = 0;
	//dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
 //   dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
 //   dwShaderFlags |= D3DXSHADER_NO_PRESHADER;

 //   HRESULT hr = D3DXCreateEffectFromFile(d3ddev, L"C:\\Users\\fcalvet\\Desktop\\direct8\\Projet8\\RollerCoaster\\Tutorial06.fx", NULL, NULL, dwShaderFlags, NULL, &g_pEffect, NULL);
 //   if (FAILED(hr))
 //   {
 //       Utils::Println(hr);
 //       Utils::Println(D3DERR_INVALIDCALL);
 //       Utils::Println(D3DXERR_INVALIDDATA);
 //       Utils::Println(E_OUTOFMEMORY);

 //   }

 //   // Obtain the techniques
 //   D3DXHANDLE g_pTechniqueRender = g_pEffect->GetTechniqueByName("Render");
 //   D3DXHANDLE g_pTechniqueRenderLight = g_pEffect->GetTechniqueByName("RenderLight");

    // Obtain the variables
    // g_pWorldVariable = g_pEffect->GetVariableByName("")->AsMatrix();
    // g_pViewVariable = g_pEffect->GetVariableByName("View")->AsMatrix();
    // g_pProjectionVariable = g_pEffect->GetVariableByName("Projection")->AsMatrix();
    // g_pLightDirVariable = g_pEffect->GetVariableByName("vLightDir")->AsVector();
    // g_pLightColorVariable = g_pEffect->GetVariableByName("vLightColor")->AsVector();
    // g_pOutputColorVariable = g_pEffect->GetVariableByName("vOutputColor")->AsVector();
}

void Engine::UninitD3D()
{
    // close and release Direct3D
    d3ddev->Release();
    d3d->Release();

    // close and release the vertex buffer
    _VBuffer->Release();
    _IBuffer->Release();

    // Audio
    AudioManager::Clean();
}

// **************************** //

void Engine::Run(HWND window)
{
    if (Application::IsPlaying())
        return;

    _window = window;

	if (_window == nullptr)
	{
		Utils::Println("A window instance must be set!");
        delete(this);
		return;
	}

	if (!SceneManager::HasScenesInBuild())
	{
		Utils::Println("There must be at least one scene in the build!");
        delete(this);
		return;
	}

    Application::playing = true;

    // *** Part 1: Initialization *** //

    InitD3D();
    SceneManager::LoadScene(1);
    AudioManager::Initialize();

    MSG msg; // this struct holds Windows event messages

    // *** Part 2: Game Loop *** //

    while (!Application::quit)
    {
        // _profiler->loopCount++;

        // Check to see if any messages are waiting in the queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        
            // If the message is WM_QUIT, exit the while loop
            if (msg.message == WM_QUIT)
                goto quit;
        }

        // Run game code here

        CheckForNewFrame();
    }
	quit:;

    // *** Part 3: Uninitialization *** //

    UninitD3D();
    SceneManager::Clean();
    AudioManager::Clean();
    Execution::Clean();
    PhysicsEngine::Clean();
    Input::Clean();
    delete(this);
}

// **************************** //

// This one is always called first
void Engine::CheckForNewFrame()
{
    // we execute a new frame each Application::targetFrameRate

    static float frameElapsed;

    if (_profiler->lastFrameTime < 0.0f) // THE first frame
    {
        _profiler->lastFrameTime = 0.0f;
        _profiler->InitSystemTime();
        NewFrame();
        return;
    }

    frameElapsed = Time::runTime() - _profiler->lastFrameTime;
    if (frameElapsed >= Application::targetFrameRate) // new frame
        NewFrame();
}

void Engine::NewFrame()
{
    // first we update all of the data

    const float time = Time::runTime();

    const float frameRate = time - _profiler->lastFrameTime; // => elapsed
    _profiler->lastFrameTime = time;

    Time::_frameCount++;
    Time::_time = time;
    Time::_deltaTime = frameRate * Time::timeScale;
    Time::_unscaledDeltaTime = frameRate;

    // then we run the frame

    _profiler->TimedRunner(_profiler->frameTime, RUNNER(RunFrame));

#if PROFILER_DISPLAY_ENABLED
    CheckForProfilerDisplay();
#endif
}

// **************************** //

void Engine::CheckForProfilerDisplay()
{
    // we display the profiler info each _profiler->displayCooldown

    static float profilerElapsed;

    if (_profiler->lastDisplayTime < 0.0f) // the first frame
    {
        _profiler->DisplayData();
        return;
    }

    profilerElapsed = Time::time - _profiler->lastDisplayTime;
    if (profilerElapsed >= _profiler->displayCooldown) // new display
        _profiler->DisplayData();
}

// ************/ Execution /************ //
D3DLIGHT9 light;
static float pos = 0.0f;
void Engine::RunFrame()
{



    Execution::CheckForSceneUpdate();
    _profiler->TimedRunner(_profiler->engineStartTime, Execution::EngineStart);
    _profiler->TimedRunner(_profiler->startTime, Execution::Start);
    CheckForNewFixedUpdate();
    _profiler->TimedRunner(_profiler->inputTime, Execution::Input);
    _profiler->TimedRunner(_profiler->updateTime, Execution::Update);
    _profiler->TimedRunner(_profiler->lateUpdateTime, Execution::LateUpdate);


    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->BeginScene();    // begins the 3D scene

    _profiler->TimedRunner(_profiler->engineUpdateTime, Execution::EngineUpdate2);
    _profiler->TimedRunner(_profiler->engineUpdateTime, Execution::EngineUpdate);

    d3ddev->EndScene();    // ends the 3D scene

    _profiler->TimedRunner(_profiler->presentTime, [=] { d3ddev->Present(NULL, NULL, NULL, NULL); }); // displays the created frame
}

void Engine::CheckForNewFixedUpdate()
{
    // we execute enough fixed updates to match Application::fixedTimestep

    static float fixedElapsed;

    const float timestep = Application::fixedTimestep; // => elapsed (constant)
    Time::_fixedDeltaTime = timestep / abs(Time::timeScale);
    Time::_fixedUnscaledDeltaTime = timestep;

    if (_profiler->lastFixedTime < 0.0f) // the first frame
    {
        NewFixedUpdate();
        return;
    }

    fixedElapsed = Time::time - _profiler->lastFixedTime;
    if (fixedElapsed >= Time::fixedDeltaTime)
    {
        static float maxTimestepRemainder = 0.0f;

        float maxTimestep = Application::maximumTimestep + maxTimestepRemainder;
        maxTimestepRemainder = 0.0f;

        while (fixedElapsed >= Time::fixedDeltaTime && maxTimestep >= Time::fixedDeltaTime) // new fixed update
        {
            fixedElapsed -= Time::fixedDeltaTime;
            maxTimestep -= Time::fixedDeltaTime;
            NewFixedUpdate();
        }

        maxTimestepRemainder += maxTimestep;
    }
}

void Engine::NewFixedUpdate()
{
    // first we update all of the data

    const float time = Time::time;

    _profiler->lastFixedTime = time;

    Time::_fixedUpdateCount++;
    Time::_fixedTime = time;

    // then we run the fixed update

    _profiler->TimedRunner(_profiler->fixedUpdateTime, Execution::FixedUpdate); // FixedUpdate
    _profiler->TimedRunner(_profiler->physicsTime, Execution::PhysicsUpdate); // Physics Engine update
}
