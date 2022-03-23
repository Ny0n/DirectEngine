#include "DontDestroyOnLoad.h"

void DontDestroyOnLoad::Start()
{
	SceneManager::DontDestroyOnLoad(gameObject);
}
