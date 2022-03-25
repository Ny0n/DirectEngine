#include "pch.h"

void PhysicsEngine::Clean()
{
}

void PhysicsEngine::Update()
{
    CheckCollisions();
}

// **************************** //

void PhysicsEngine::CheckCollisions()
{

    /*if (!SceneManager::IsEmpty())
        return;*/

    list<AlignedBox*> alignedBoxes = {};
    list<GameObject*> gameObjects = {};
    list<Collider*> colliders = {};

    auto forAllGo = [&](GameObject* go) mutable
    {
        auto tmpAb = go->GetComponent<AlignedBox>();
        if (tmpAb != nullptr)
        {
            alignedBoxes.push_back(tmpAb);
        }
    };

    SceneManager::ForEachGameObject(forAllGo);

    if (alignedBoxes.empty())
        return;

    for (AlignedBox* box : alignedBoxes)
    {
        colliders = box->AreIn(SceneManager::GetAllGameObjects());
    }

    if (colliders.empty())
        return;

    Collider** arr = static_cast<Collider**>(malloc(sizeof(Collider*) * colliders.size()));

    int k = 0;
    for (Collider* const collider : colliders) {
        arr[k++] = collider;
    }

    for (int i = 0; i < colliders.size() - 1; i++)
    {
        for (int j = i + 1; j < colliders.size(); j++)
        {
            if (arr[i]->IsColliding(arr[j]))
            {
                Utils::Println("oui");
            }
        }
    }

    free(arr);
}
