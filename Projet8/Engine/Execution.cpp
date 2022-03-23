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
    {
        SceneManager::ApplyChanges();

        // while we're at it, we check inside the started components if some of them are now nullptr,
        // because they were destroyed by the scene change,
        // in that case, we remove them from the lists

        // list<Component*> sEComponents = {};
        // list<Component*> sComponents = {};
        //
        // for (Component* comp : startedEngineComponents)
        // {
	       //  try
	       //  {
        //         comp->GetType();
	       //  }
	       //  catch (...)
	       //  {
	       //  }
        //     Utils::Println(comp->GetType());
        //     if (comp != nullptr)
        //     {
        //         sEComponents.push_back(comp);
        //     }
        // }
        //
        // for (auto comp : startedComponents)
        // {
        //     if (comp != nullptr)
        //     {
        //         sComponents.push_back(comp);
        //     }
        // }
        //
        // startedEngineComponents = sEComponents;
        // startedComponents = sComponents;

        startedEngineComponents.clear();
        startedComponents.clear();
    }
}
