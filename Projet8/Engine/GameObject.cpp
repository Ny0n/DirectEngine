#include "pch.h"

#include "GameObject.h"

#include "Utils.h"

GameObject::GameObject()
{
	transform =new Transform();
}

GameObject::~GameObject()
{
	for (Component* component : components)
	{
		delete(component);
	}
	components.clear();
}

Component* GameObject::GetComponent(ComponentType type)
{
	for (Component* component : components)
	{
		if (component->typeEquals(type))
			return component;
	}
}

bool GameObject::AddComponent(Component* component)
{
	for (Component* element : components)
	{
		if (element->typeEquals(component))
			return false;
	}

	components.push_back(component);
	return true;
}

bool GameObject::RemoveComponent(ComponentType type)
{
	for (Component* element : components)
	{
		if (element->typeEquals(type))
		{
			components.remove(element);
			delete(element);
			return true;
		}
	}
	return false;
}

bool GameObject::RemoveComponent(Component* component)
{
	for (Component* element : components)
	{
		if (element->typeEquals(component))
		{
			components.remove(element);
			delete(element);
			return true;
		}
	}
	return false;
}
