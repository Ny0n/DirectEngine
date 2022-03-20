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

	void NewFrame();
	void RunFrame();

	void Input();
	void Start();
	void Update();

	Scene* _scene;
	list<Component*> _startedComponents;

};
