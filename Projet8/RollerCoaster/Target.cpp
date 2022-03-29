#include "Target.h"

void Target::removeSelf()
{
	
	_listGameObject->remove(gameObject);
}

void Target::Update()
{
	Utils::Println(_listGameObject->size());
}
