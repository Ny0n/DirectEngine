﻿#include "AudioTester.h"

AudioTester::AudioTester()
{
}

AudioTester::~AudioTester()
{
}

// **************************** //

// Start is called before the first frame update
void AudioTester::Start()
{
	_source = gameObject->GetComponent<AudioSource>();
	if (_source != nullptr)
		_source->SetSound(L"Audio\\music.wav");
}

// Update is called once per frame
void AudioTester::Update()
{
	if (_source == nullptr)
		return;

	if (Input::GetKeyDown(KeyCode::Escape))
	{
		Application::Quit();
	}

	if (Input::GetKeyDown(KeyCode::A))
	{
		_source->Play();
	}

	if (Input::GetKeyDown(KeyCode::Z))
	{
		_source->Pause();
	}

	if (Input::GetKeyDown(KeyCode::E))
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
		_source->SetVolume(_source->GetVolume() - 1.0f);
	}

	if (Input::GetKeyDown(KeyCode::Alpha4))
	{
		_source->SetVolume(_source->GetVolume() + 1.0f);
	}

	if (Input::GetKeyDown(KeyCode::Alpha5))
	{
		_source->SetSound(L"Audio\\gnome.wav");
	}
}