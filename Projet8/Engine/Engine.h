#pragma once

class Component;
class Scene;

class Engine final
{

public:
	static Engine* GetInstance() // Singleton
	{
		static auto instance = new Engine();
		return instance;
	}
	Engine(Engine const&) = delete;
	Engine(Engine const&&) = delete;
	void operator=(Engine const&) = delete;
	void operator=(Engine const&&) = delete;

	void LoadScene(Scene* scene);

	void Run(HWND window);

private:
	Engine(); // Only accessible from GetInstance()
	~Engine();

	bool _isPlaying;

	HWND _window;
	Profiler* _profiler;

	void InitLight();
	void InitD3D();
	void UninitD3D();

	void CheckForNewFrame();
	void CheckForNewFixedUpdate();
	void CheckForProfilerDisplay();

	void NewFrame();
	void RunFrame();
	void Input();
	void Start();
	void Update();
	void LateUpdate();

	void NewFixedUpdate();
	void FixedUpdate();

	Scene* _scene;
	list<Component*> _startedComponents;

};

/*
 * Frame Order of Execution:
 *
 *		Start()			// Start is only ever called once for a given script
 *
 *		FixedUpdate()	// This may be called 0, 1 or multiple times per frame depending on the frame rate, but will ALWAYS be called 1/timestep times per second
 *		<Physics>		// The Physics update cycle happens immediatly after the FixedUpdate call
 *
 *		<Input events>	// Updates all inputs (inside the Input class)
 *		Update()
 *		LateUpdate()
 *
 *		<DrawFrame>		// The frame GPU drawing happens after everything
 *
 *		<Profiler>		// Displays the profiler info for the frame
 *
 *		<Quit>			// If Application::Quit() is called inside the frame, we exit the game now
 *
 */
