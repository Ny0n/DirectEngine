#pragma once

class Engine final
{

public:
	static Engine* GetInstance() // Singleton
	{
		if (instance == nullptr)
			instance = new Engine();

		return instance;
	}
	Engine(Engine const&) = delete;
	Engine(Engine const&&) = delete;
	void operator=(Engine const&) = delete;
	void operator=(Engine const&&) = delete;

	void Run(HWND window);

	const HWND& window;

private:
	static Engine* instance; // Only accessible from GetInstance()
	Engine();
	~Engine();

	HWND _window;
	Profiler* _profiler;
	
	void InitD3D();
	void UninitD3D();

	void CheckForNewFrame();
	void CheckForNewFixedUpdate();
	void CheckForProfilerDisplay();

	void NewFrame();
	void NewFixedUpdate();
	void RunFrame();

};

/*
 * Order of Execution (for each frame):
 *
 *		<Scene Changes>	// If it was requested during the laft frame, we load the new scene
 *
 *		EngineStart()	// The Start() for Engine components, see below
 *		Start()			// Called only once, either the first frame after a scene load, or if we are at runtime: at Instantiate(GameObject* go) OR AddComponent<>() (instantly IF the component is enabled), OR at SetEnabled(true) (instantly) if it's the first time we enable the component
 *
 *		FixedUpdate()	// This may be called 0, 1 or multiple times per frame depending on the frame rate, but will ALWAYS be called 1/timestep times per second
 *		<Physics>		// The Physics update cycle happens immediatly after the FixedUpdate call
 *
 *		<Input events>	// Updates all inputs (inside the Input class)
 *		Update()
 *		LateUpdate()
 *		EngineUpdate()	// The Update() for Engine components
 *
 *		<DrawFrame>		// The frame GPU drawing happens after everything
 *
 *		<Profiler>		// Displays the profiler info for the frame
 *
 *		<Quit>			// If Application::Quit() is called inside the frame, we exit the game now
 *
 *	Specific calls:
 *	
 *		Awake()			// Called only once, either at Instantiate(GameObject* go) OR AddComponent<>() (instantly) or when the scene is loaded (CALLED EVEN IF THE GO IS DISABLED ON INSTANTIATION)
 *		OnEnable()		// Called each time its enabled state passes from disabled to enabled
 *		OnDisable()		// Called each time its enabled state passes from enabled to disabled
 *		OnDestroy()		// Called only once, either at Destroy(GameObject* go) OR RemoveComponent<>() (instantly) or when the scene is unloaded
 *
 */
