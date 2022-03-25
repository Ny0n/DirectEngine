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

	void InitLight();
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
 *		<Scene Changes>	// If it was requested during the laft frame, we load the new scene, or we Instantiate/Destroy GameObjects
 *
 *		EngineStart()	// The Start() for Engine components, executed BEFORE anything else
 *		Start()			// Start is only ever called once for a given script
 *
 *		FixedUpdate()	// This may be called 0, 1 or multiple times per frame depending on the frame rate, but will ALWAYS be called 1/timestep times per second
 *		<Physics>		// The Physics update cycle happens immediatly after the FixedUpdate call
 *
 *		<Input events>	// Updates all inputs (inside the Input class)
 *		Update()
 *		LateUpdate()
 *		EngineUpdate()	// The Update() for Engine components, executed AFTER everything else
 *
 *		<DrawFrame>		// The frame GPU drawing happens after everything
 *
 *		<Profiler>		// Displays the profiler info for the frame
 *
 *		<Quit>			// If Application::Quit() is called inside the frame, we exit the game now
 *
 */
