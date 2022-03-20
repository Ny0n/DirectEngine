#include "pch.h"

// **************************** //

LPDIRECT3D9 d3d; // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev; // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 _VBuffer = nullptr;
LPDIRECT3DINDEXBUFFER9 _IBuffer = nullptr;

// **************************** //

Engine::Engine() : _isPlaying(false), _window(nullptr), _profiler(new Profiler()), _scene(nullptr)
{
    Time::_profiler = _profiler;
}

Engine::~Engine()
{
    delete(_profiler);
    delete(_scene);
    _startedComponents.clear();
}

void Engine::LoadScene(Scene* scene)
{
    _scene = scene;
}

// **************************** //

void Engine::InitLight()
{
    D3DLIGHT9 light;    // create the light struct
    D3DMATERIAL9 material;    // create the material struct

    ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
    light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
    light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
    light.Direction = D3DXVECTOR3(0.0f, -0.3f, 0.0f);

    d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
    d3ddev->LightEnable(0, TRUE);    // turn on light #0

    ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
    material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

    d3ddev->SetMaterial(&material);    // set the globably-used material to &material
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

    InitLight();
    
    d3ddev->SetRenderState(D3DRS_LIGHTING, true);    // turn on the 3D lighting
    d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(155, 155, 155));    // ambient light
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer

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
}

void Engine::UninitD3D()
{
    // close and release Direct3D
    d3ddev->Release();
    d3d->Release();

    // close and release the vertex buffer
    _VBuffer->Release();
    _IBuffer->Release();
}

// **************************** //

void Engine::Run(HWND window)
{
    if (_isPlaying)
        return;

    _window = window;

	if (_window == nullptr)
	{
		Utils::Println("A window instance must be set!");
		return;
	}

	if (_scene == nullptr)
	{
		Utils::Println("A default scene must be set!");
		return;
	}

    _isPlaying = true;

    // *** Part 1: Initialization *** //

    InitD3D();

    MSG msg; // this struct holds Windows event messages

    // starting the profiler
    _profiler->InitSystemTime();

    // initializing variables
    float frameElapsed;
    float fixedElapsed;
    float profilerElapsed;

    // *** Part 2: Game Loop *** //

    NewFrame(); // starting frame

#if PROFILER_DISPLAY_ENABLED
    _profiler->DisplayData(); // displaying the data of the first frame
#endif

    while (true)
    {
        // _profiler->loopCount++;

        if (Application::quit)
            break;

        // Check to see if any messages are waiting in the queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        
            // If the message is WM_QUIT, exit the while loop
            if (msg.message == WM_QUIT)
                goto stop;
        }

        // Run game code here

        _profiler->runTime = _profiler->GetSystemTime();
        fixedElapsed = _profiler->runTime - _profiler->lastFixedTime;
        if (fixedElapsed >= Application::fixedTimestep) // new fixed update
            NewFixedUpdate(); // TODO maybe redo this and put in NewFrame with a while? (new Start() can be called after a fixedupdate..)

        _profiler->runTime = _profiler->GetSystemTime();
        frameElapsed = _profiler->runTime - _profiler->lastFrameTime;
        if (frameElapsed >= Application::targetFrameRate) // new frame
            NewFrame();

#if PROFILER_DISPLAY_ENABLED
        _profiler->runTime = _profiler->GetSystemTime();
    	profilerElapsed = _profiler->runTime - _profiler->lastDisplayTime;
        if (profilerElapsed >= _profiler->displayCooldown)
            _profiler->DisplayData();
#endif
    }
	stop:;

    // *** Part 3: Uninitialization *** //

    UninitD3D();
    Input::Delete();
    delete(this);
}

// **************************** //

void Engine::NewFrame()
{
    // first we update all of the data

    _profiler->currentFrameRate = _profiler->runTime - _profiler->lastFrameTime; // => elapsed
    _profiler->lastFrameTime = _profiler->runTime;
    
    _profiler->currentFPS = _profiler->currentFrameRate == 0.0f ? 0.0f : 1.0f / _profiler->currentFrameRate;

    Time::_frameCount++;
    Time::_time = _profiler->runTime;
    Time::_deltaTime = _profiler->currentFrameRate * Time::timeScale;
    Time::_unscaledDeltaTime = _profiler->currentFrameRate;

    // then we run the frame

    _profiler->TimedRunner(_profiler->frameTime, RUNNER(RunFrame));
}

void Engine::NewFixedUpdate()
{
    // first we update all of the data

    _profiler->currentFixedRate = _profiler->runTime - _profiler->lastFixedTime; // => elapsed
    _profiler->lastFixedTime = _profiler->runTime;

    Time::_fixedUpdateCount++;
    Time::_fixedTime = _profiler->runTime;
    Time::_fixedDeltaTime = _profiler->currentFixedRate * Time::timeScale;
    Time::_fixedUnscaledDeltaTime = _profiler->currentFixedRate;

    // then we run the fixed update

    Time::_inFixedUpdateStep = true; _profiler->TimedRunner(_profiler->fixedUpdateTime, RUNNER(FixedUpdate)); Time::_inFixedUpdateStep = false;
}

// ************/ Execution /************ //

void Engine::RunFrame()
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();    // begins the 3D scene

    _profiler->TimedRunner(_profiler->inputTime, RUNNER(Input));
    Time::_inStartStep = true; _profiler->TimedRunner(_profiler->startTime, RUNNER(Start)); Time::_inStartStep = false;
    Time::_inUpdateStep = true; _profiler->TimedRunner(_profiler->updateTime, RUNNER(Update)); Time::_inUpdateStep = false;

    d3ddev->EndScene();    // ends the 3D scene

    _profiler->TimedRunner(_profiler->presentTime, [=] { d3ddev->Present(NULL, NULL, NULL, NULL); }); // displays the created frame
}

// ************/ Execution Order /************ //

void Engine::Input()
{
    Input::UpdateInputs();
}

void Engine::Start() // TODO optimize this (init once a new list with all starts and then remove ?)
{
    for (GameObject* go : _scene->gameObjects)
    {
        for (Component* comp : go->components)
        {
            if (Utils::Contains(&_startedComponents, comp) == false)
            {
                _startedComponents.push_back(comp);
                comp->Start();
            }
        }
    }
}

void Engine::Update()
{
    for (GameObject* go : _scene->gameObjects)
    {
        for (Component* comp : go->components)
        {
            comp->Update();
        }
    }
}

void Engine::FixedUpdate()
{
    for (GameObject* go : _scene->gameObjects)
    {
        for (Component* comp : go->components)
        {
            comp->FixedUpdate();
        }
    }
}
