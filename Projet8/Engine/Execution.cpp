#include "pch.h"

list<Object*> Execution::markedForInstantiation = {};
list<Object*> Execution::markedForDestruction = {};

void Execution::Clean()
{
}

// ************/ Execution Order /************ //

void Execution::EngineStart()
{
    SceneManager::ForEachComponent([](Component* component)
    {
        if (!component->_engineStarted)
        {
            component->EngineStart();
            component->_engineStarted = true;
        }
    });
}

// **************************** //

void Execution::Start()
{
    Time::_inStartStep = true;

    SceneManager::ForEachComponent([](Component* component)
    {
        if (!component->_started)
        {
            component->Start();
            component->_started = true;
        }
    });

    Time::_inStartStep = false;
}

// **************************** //

void Execution::FixedUpdate()
{
    Time::_inFixedUpdateStep = true;

    SceneManager::ForEachComponent([](Component* component)
    {
        component->FixedUpdate();
    });

    Time::_inFixedUpdateStep = false;
}

// **************************** //

void Execution::PhysicsUpdate()
{
	PhysicsEngine::Update();
}

// **************************** //

void Execution::Input()
{
    Input::UpdateInputs();
}

// **************************** //

void Execution::Update()
{
    Time::_inUpdateStep = true;
    
    SceneManager::ForEachComponent([](Component* component)
    {
        component->Update();
    });

    Time::_inUpdateStep = false;
}

// **************************** //

void Execution::LateUpdate()
{
    Time::_inLateUpdateStep = true;

    SceneManager::ForEachComponent([](Component* component)
    {
        component->LateUpdate();
    });

    Cursor::CursorUpdate();

    Time::_inLateUpdateStep = false;
}

// **************************** //

void Execution::EngineUpdate()
{
    SceneManager::ForEachComponent([](Component* component)
    {
        component->EngineUpdate();
    });
}

void Execution::CheckForSceneUpdate()
{
    // we Instantiate/Destroy what needs to be

    // Instantiation
    if (!markedForInstantiation.empty())
    {
	    for (auto obj : markedForInstantiation)
            obj->_markedForInstantiation = false; // the obj is now alive!

        markedForInstantiation.clear();
    }

    // Destruction
    if (!markedForDestruction.empty())
    {
        list<Object*> copy(markedForDestruction); // safeguard

        for (auto obj : copy)
            Object::TryToDelete(obj);

        copy.clear();

        markedForDestruction.clear();
    }

    // we update (load/unload/additive) the scene if we have to
    if (SceneManager::ChangeRequired())
        SceneManager::ApplyChanges();
}
