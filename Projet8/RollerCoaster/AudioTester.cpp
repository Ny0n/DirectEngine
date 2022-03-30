#include "AudioTester.h"

AudioTester* SceneSingleton<AudioTester>::Instance;

AudioTester::AudioTester()
{
}

AudioTester::~AudioTester()
{
}

// **************************** //

LPCWSTR tbl[3];
static int i = 0;

// Start is called before the first frame update
void AudioTester::Start()
{
	tbl[0] = L"Audio\\gnome.wav";
	tbl[1] = L"Audio\\waka.wav";
	tbl[2] = L"Audio\\music.wav";

	_source = gameObject->GetComponent<AudioSource>();
	// if (_source != nullptr)
	// 	_source->SetSound(tbl[0]);
}

// Update is called once per frame
void AudioTester::Update()
{
	return;

	if (_source == nullptr)
		return;

	// if (Input::GetKeyDown(KeyCode::Escape))
	// {
	// 	Application::Quit();
	// }

	if (Input::GetKeyDown(KeyCode::A))
	{
		_source->Play();
	}

	if (Input::GetKeyDown(KeyCode::Z))
	{
		_source->Resume();
	}

	if (Input::GetKeyDown(KeyCode::E))
	{
		_source->Pause();
	}

	if (Input::GetKeyDown(KeyCode::S))
	{
		_source->Stop();
	}

	if (Input::GetKeyDown(KeyCode::F))
	{
		_source->Toggle();
	}

	if (Input::GetKeyDown(KeyCode::R))
	{
		_source->Restart();
	}

	if (Input::GetKeyDown(KeyCode::Alpha3))
	{
		_source->SetVolume(_source->GetVolume() - 0.2f);
	}

	if (Input::GetKeyDown(KeyCode::Alpha4))
	{
		_source->SetVolume(_source->GetVolume() + 0.2f);
	}

	if (Input::GetKeyDown(KeyCode::Alpha5))
	{
		i++;
		if (i > 2)
			i = 0;

		_source->SetSound(tbl[i]);
	}

	if (Input::GetKeyDown(KeyCode::L))
	{
		_source->SetLooping(!_source->IsLooping());
		Utils::Println(_source->IsLooping());
	}

	if (Input::GetKeyDown(KeyCode::T))
	{
		// _source->Testing();
	}

	if (Input::GetKeyDown(KeyCode::Alpha1))
	{
		Utils::Println(1);
	}

	// if (Input::GetKeyDown(KeyCode::Escape))
	// {
	// 	Application::Quit();
	// }
}
