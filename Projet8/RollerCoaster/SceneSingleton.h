#pragma once

#include "EngineLib.h"

template <typename T>
class SceneSingleton : public MonoBehaviour // if a script extends from this class, it makes it unique in the scene. if another is created, it immediatly destroys its gameObject
{
	string GetType() override { return NAMEOF(SceneSingleton); }

	void Awake() final;
    bool _singletonDestroy = false;

public:
    static T* Instance;

    SceneSingleton() = default;
    ~SceneSingleton() override
	{
        if (!_singletonDestroy)
            Instance = nullptr;

        _singletonDestroy = false;
    }

protected:
    virtual bool DontDestroyOnLoad() { return true; }
	virtual void SingletonAwake() {}
    
};

template <typename T>
void SceneSingleton<T>::Awake()
{
    if (Instance == nullptr)
    {
        Utils::Println("INIT SINGLETON");

        Instance = static_cast<T*>(this);
        if (DontDestroyOnLoad())
            SceneManager::DontDestroyOnLoad(gameObject);

        SingletonAwake();
    }
    else
    {
        Utils::Println("DESTROY SINGLETON");
        _singletonDestroy = true;
        Destroy(gameObject);
    }
}
