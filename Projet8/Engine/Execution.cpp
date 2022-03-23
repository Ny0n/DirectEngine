#include "pch.h"

list<Component*> Execution::startedEngineComponents = {};
list<Component*> Execution::startedComponents = {};

void Execution::Clean()
{
    startedComponents.clear();
    startedEngineComponents.clear();
}

// ************/ Execution Order /************ //

void EngineStart_(Component* component)
{
    if (!Utils::Contains(&Execution::startedEngineComponents, component))
    {
	    Execution::startedEngineComponents.push_back(component);
        component->EngineStart();
    }
}

void Execution::EngineStart()
{
    SceneManager::ForEachComponent(EngineStart_);
}

// **************************** //

void Start_(Component* component)
{
    if (!Utils::Contains(&Execution::startedComponents, component))
    {
	    Execution::startedComponents.push_back(component);
        component->Start();
    }
}

void Execution::Start()
{
    Time::_inStartStep = true;

    SceneManager::ForEachComponent(Start_);

    Time::_inStartStep = false;
}

// **************************** //

void FixedUpdate_(Component* component)
{
    component->FixedUpdate();
}

void Execution::FixedUpdate()
{
    Time::_inFixedUpdateStep = true;

    SceneManager::ForEachComponent(FixedUpdate_);

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

void Update_(Component* component)
{
    component->Update();
}

void Execution::Update()
{
    Time::_inUpdateStep = true;

    SceneManager::ForEachComponent(Update_);

    Time::_inUpdateStep = false;
}

// **************************** //

void LateUpdate_(Component* component)
{
    component->LateUpdate();
}

void Execution::LateUpdate()
{
    Time::_inLateUpdateStep = true;

    Cursor::CursorUpdate();
    SceneManager::ForEachComponent(LateUpdate_);

    Time::_inLateUpdateStep = false;
}

// **************************** //

void EngineUpdate_(Component* component)
{
    component->EngineUpdate();
}

void Execution::EngineUpdate()
{
    SceneManager::ForEachComponent(EngineUpdate_);
}

void Execution::CheckForSceneUpdate()
{
    // we update (load/unload/additive) the scene if we have to
    if (SceneManager::ChangeRequired())
        SceneManager::ApplyChanges();
}
