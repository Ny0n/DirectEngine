#pragma once

#include "EngineLib.h"

template <typename T>
class SceneSingleton : public MonoBehaviour // if a script extends from this class, it makes it unique in the scene. if another is created, it immediatly destroys its gameObject
{
	string GetType() override { return NAMEOF(SceneSingleton); }

    static T* Instance;
	void Awake() final;
    bool singletonDestroy = false;

public:
    SceneSingleton() = default;
    ~SceneSingleton() override
	{
        if (!singletonDestroy)
            Instance = nullptr;

        singletonDestroy = false;
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
        singletonDestroy = true;
        Destroy(gameObject);
    }
}
