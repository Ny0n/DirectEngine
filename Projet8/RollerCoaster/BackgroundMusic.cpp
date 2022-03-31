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

// Update is called once per frame
void BackgroundMusic::Update()
{
	return;

	if (source == nullptr)
		return;

	// if (Input::GetKeyDown(KeyCode::Escape))
	// {
	// 	Application::Quit();
	// }

	if (Input::GetKeyDown(KeyCode::A))
	{
		source->Play();
	}

	if (Input::GetKeyDown(KeyCode::Z))
	{
		source->Resume();
	}

	if (Input::GetKeyDown(KeyCode::E))
	{
		source->Pause();
	}

	if (Input::GetKeyDown(KeyCode::S))
	{
		source->Stop();
	}

	if (Input::GetKeyDown(KeyCode::F))
	{
		source->Toggle();
	}

	if (Input::GetKeyDown(KeyCode::R))
	{
		source->Restart();
	}

	if (Input::GetKeyDown(KeyCode::Alpha3))
	{
		source->SetVolume(source->GetVolume() - 0.2f);
	}

	if (Input::GetKeyDown(KeyCode::Alpha4))
	{
		source->SetVolume(source->GetVolume() + 0.2f);
	}

	if (Input::GetKeyDown(KeyCode::Alpha5))
	{
		LPCWSTR tbl[3];
		static int i = 0;
		
		tbl[0] = L"Audio\\gnome.wav";
		tbl[1] = L"Audio\\waka.wav";
		tbl[2] = L"Audio\\music.wav";

		i++;
		if (i > 2)
			i = 0;

		source->SetSound(tbl[i]);
	}

	if (Input::GetKeyDown(KeyCode::L))
	{
		source->SetLooping(!source->IsLooping());
		Utils::Println(source->IsLooping());
	}

	if (Input::GetKeyDown(KeyCode::T))
	{
		// _source->Testing();
	}

	if (Input::GetKeyDown(KeyCode::Alpha1))
	{
		Utils::Println(1);
	}
}
