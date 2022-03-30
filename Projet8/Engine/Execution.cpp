#include "pch.h"

list<Object*> Execution::markedForDestruction = {};

void Execution::Clean()
{
    markedForDestruction.clear();
}

// ************/ Execution Order /************ //

void Execution::EngineStart()
{
    SceneManager::ForEachComponent([](Component* component)
    {
        component->CheckIfEngineStarted();
    });
}

// **************************** //

void Execution::Start()
{
    Time::_inStartStep = true;

    SceneManager::ForEachComponent([](Component* component)
    {
        component->CheckIfStarted();
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
    Time::_inSceneStep = true;

    // we Destroy what needs to be
    if (!markedForDestruction.empty())
    {
        list<Object*> copy(markedForDestruction); // safeguard
        markedForDestruction.clear();

        for (auto obj : copy)
            Object::TryToDelete(obj);

        copy.clear();
    }

    // we update (load/unload/additive) the scene if we have to
    if (SceneManager::ChangeRequired())
        SceneManager::ApplyChanges();

    Time::_inSceneStep = false;
}