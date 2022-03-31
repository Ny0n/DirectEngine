#include "BackgroundMusic.h"

BackgroundMusic* SceneSingleton<BackgroundMusic>::Instance;

BackgroundMusic::BackgroundMusic()
{
}

BackgroundMusic::~BackgroundMusic()
{
}

// **************************** //

// Start is called before the first frame update
void BackgroundMusic::Start()
{
	source = gameObject->GetComponent<AudioSource>();
}
