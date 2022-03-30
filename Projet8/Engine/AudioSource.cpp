#include "pch.h"

AudioSource::AudioSource()
{
	pSourceCallback = new AudioManager::AudioSourceCallbacks();
	pSourceCallback->source = this;
}

AudioSource::~AudioSource()
{
	pSourceVoice->DestroyVoice();
}

// **************************** //

// EngineStart is called once, before the MonoBehaviour Start
void AudioSource::EngineStart()
{
}

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void AudioSource::EngineUpdate()
{
}

// **************************** //

void AudioSource::SetSound(LPCWSTR fileName)
{
	if (pSourceVoice != nullptr)
		Stop();

	// Sound data

	// ** Init ** //

	wfx = { 0 };
	buffer = { 0 };

	// ** Open the audio file ** //

	HANDLE hFile = CreateFile(
		fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		Utils::PrintError(__FILE__, __LINE__, L"INVALID_HANDLE_VALUE audio error");
		Utils::Println(HRESULT_FROM_WIN32(GetLastError()));
		return;
	}

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
	{
		Utils::PrintError(__FILE__, __LINE__, L"INVALID_SET_FILE_POINTER audio error");
		Utils::Println(HRESULT_FROM_WIN32(GetLastError()));
		return;
	}

	// ** Locate the "RIFF" block in the wav file ** //

	DWORD dwChunkSize;
	DWORD dwChunkPosition;

	//check the file type, should be fourccWAVE or 'XWMA'
	AudioManager::FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	AudioManager::ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

	if (filetype != fourccWAVE)
	{
		Utils::PrintError(__FILE__, __LINE__, L"ReadChunkData audio error");
		return;
	}

	// ** Locate the "fmt" segment ** //

	AudioManager::FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	AudioManager::ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	// ** Fill out the audio data buffer with the contents of the fourccDATA chunk ** //

	AudioManager::FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	AudioManager::ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	// ** Remplissage de la  _ mémoire tampon XAUDIO2 ** //

	buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
	buffer.pAudioData = pDataBuffer;  //buffer containing audio data
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	UpdateLooping();

	// Sound Player
	HRSOUND(AudioManager::pXAudio2->CreateSourceVoice(&pSourceVoice, reinterpret_cast<WAVEFORMATEX*>(&wfx), 0, XAUDIO2_DEFAULT_FREQ_RATIO, pSourceCallback)); // WARNING: Crashes if no output device is set on the system!
}

#define CHECKSOURCE(x)\
if (pSourceVoice == nullptr)\
{\
	Utils::Println("You must set a sound to the Audio Source!");\
	return x;\
}

// **************************** //

COM_DECLSPEC_NOTHROW void AudioManager::AudioSourceCallbacks::OnBufferEnd(void* pBufferContext)
{
	Utils::Println("END " + to_string(source->_playing));

	// HRSOUND(source->pSourceVoice->Stop());
	// // Utils::Println(Time::runTime());
	//
	if (source->_ended)
	{
		source->_ended = false;
		return;
	}
	//
	// Utils::Println("--> PASSED?!");
	//
	// return;
	//
	// if (source->_restarting)
	// {
	// 	source->_restarting = false;
	// 	return;
	// }
	
	source->_playing = false;
	source->_paused = false;

	Utils::Println("SET PLAYING FALSE");
	
	if (!source->_wasPlaying) // if this is false, it means we want to start looping
	{
		Utils::Println("NOPE");
		return;
	}
	
	source->_wasPlaying = false;
	
	Utils::Println("Restarting...");
	source->Play(); // the callback when a loop ends is OnLoopEnd, so we won't get back here
}

void AudioManager::AudioSourceCallbacks::OnLoopEnd(void* pBufferContext)
{
	Utils::Println("LOOP END");
}

// **************************** //

void AudioSource::Play()
{
	CHECKSOURCE()
	
	if (_paused)
	{
		Resume();
		return;
	}
	
	if (_playing)
		return;
	
	HRSOUND(Flush());
	HRSOUND(Submit());
	// HRSOUND(pSourceVoice->FlushSourceBuffers());
	// HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer));

	HRSOUND(pSourceVoice->Start());

	_playing = true;
	Utils::Println("WTF");
}

void AudioSource::Resume()
{
	CHECKSOURCE()
	
	if (!_paused)
		return;
	
	HRSOUND(pSourceVoice->Start());

	_paused = false;
}

void AudioSource::Pause()
{
	CHECKSOURCE()
	
	if (!_playing || _paused)
		return;

	HRSOUND(pSourceVoice->Stop());
	
	_paused = true;
}

void AudioSource::Toggle()
{
	CHECKSOURCE()

	if (_paused)
		Play();
	else
		Pause();
}

void AudioSource::Stop()
{
	CHECKSOURCE()
		
	HRSOUND(pSourceVoice->Stop());
	// HRSOUND(pSourceVoice->FlushSourceBuffers());
	HRSOUND(Flush());

	_playing = false;
	_paused = false;
}

void AudioSource::Restart()
{
	CHECKSOURCE()

	// _restarting = true;
	HRSOUND(pSourceVoice->Stop());
	HRSOUND(Flush());
	HRSOUND(Submit());
	HRSOUND(pSourceVoice->Start());
	_playing = true;
	Utils::Println("SET PLAYING TRUE");

	// HRSOUND(pSourceVoice->Stop());
	// HRSOUND(pSourceVoice->FlushSourceBuffers());
	// HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer));
	// HRSOUND(pSourceVoice->Start());

	// Stop();
	// Play();
	// Utils::Println("PLAYING:");
	// Utils::Println(_playing);
}

void AudioSource::Testing()
{
	// Utils::Println("TESTING");
	
	HRSOUND(pSourceVoice->Stop());
	Utils::Println("a");
	Utils::Println(Time::runTime());
	HRSOUND(Flush());
	Utils::Println("b");
	Utils::Println(Time::runTime());
	// HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer));
	// HRSOUND(pSourceVoice->Start());
	// Utils::Println("after");

	// _playing = false;
	// _paused = false;
}

HRESULT AudioSource::Flush()
{
	if (_hasBuffer)
	{
		Utils::Println("FLUSHING");

		// TODO change macro or don't use it, to change _hasBuffer only if succeded
		pSourceVoice->FlushSourceBuffers(); // THIS LINE only triggers an end callback IF we flush an UNFINISHED buffer

		if (_playing) // so we're checking that here, and saying "hey, we terminated an unfinished buffer, expect an unnessary callback)
			_ended = true;

		Utils::Println("FLUSHED");

		_hasBuffer = false;
	}

	return S_OK;
}

HRESULT AudioSource::Submit()
{
	if (!_hasBuffer)
	{
		Utils::Println("SUBMITTING");

		pSourceVoice->SubmitSourceBuffer(&buffer);

		Utils::Println("SUBMITTED");

		_hasBuffer = true;
	}

	return S_OK;
}

// **************************** //

bool AudioSource::IsLooping()
{
	return _isLooping;
}

void AudioSource::SetLooping(bool loop)
{
	CHECKSOURCE()

	if (_isLooping == loop)
		return;

	_isLooping = loop;

	UpdateLooping();

	if (_isLooping)
	{
		if (_playing)
		{
			_wasPlaying = true;
			Utils::Println("WASPLAYING SET");
		}
	}
	else
	{
		HRSOUND(pSourceVoice->ExitLoop());
		_wasPlaying = false;
		Utils::Println("WASPLAYING UNSET");
	}
}

void AudioSource::UpdateLooping()
{
	if (_isLooping)
	{
		buffer.LoopBegin = buffer.PlayBegin;
		buffer.LoopLength = buffer.PlayLength;
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else
	{
		buffer.LoopBegin = 0;
		buffer.LoopLength = 0;
		buffer.LoopCount = 0;
	}
}

float AudioSource::GetVolume()
{
	CHECKSOURCE(0.0f)

	float ref = 0.0f;
	pSourceVoice->GetVolume(&ref);
	return ref;
}

// **************************** //

void AudioSource::SetVolume(float volume)
{
	CHECKSOURCE()

	if (volume >= MIN_VOLUME && volume <= MAX_VOLUME)
		pSourceVoice->SetVolume(volume);
}

// **************************** //

bool AudioSource::IsPlaying()
{
	return _playing;
}

bool AudioSource::IsPaused()
{
	return _paused;
}
