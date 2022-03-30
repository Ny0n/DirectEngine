#include "pch.h"

AudioSource::AudioSource()
{
	pSourceCallback = new AudioManager::AudioSourceCallbacks();
	pSourceCallback->source = this;
}

AudioSource::AudioSource(LPCWSTR defaultFileName, bool playOnStart, float defaultVolume, bool isLooping) : AudioSource()
{
	_fileName = defaultFileName;
	_playOnStart = playOnStart;
	SetVolume(defaultVolume);
	SetLooping(isLooping);
}

AudioSource::~AudioSource()
{
}

// **************************** //

// EngineStart is called once, before the MonoBehaviour Start
void AudioSource::EngineStart()
{
	SetSound(_fileName);
	if (_playOnStart)
		Play();
}

// EngineUpdate is called once per frame, after the MonoBehaviour Update & LateUpdate
void AudioSource::EngineUpdate()
{
}

void AudioSource::OnEnable()
{
	if (!_wasPaused)
		Resume();
}

void AudioSource::OnDisable()
{
	_overrideEnabledCheck = true;
	_wasPaused = _paused;
	Pause();
	_overrideEnabledCheck = false;
}

void AudioSource::OnDestroy()
{
	pSourceVoice->DestroyVoice();
}

// **************************** //

#define CHECKENABLED(x)\
if (!_overrideEnabledCheck && !IsEnabled())\
{\
	Utils::Println("WARNING: Cannot modify the AudioSource while it is disabled!");\
	return x;\
}

#define CHECKSOURCE(x)\
if (pSourceVoice == nullptr)\
{\
	Utils::Println("You must set a sound to the Audio Source!");\
	return x;\
}\
CHECKENABLED(x)

LPCWSTR AudioSource::GetSound()
{
	return _fileName;
}

void AudioSource::SetSound(LPCWSTR fileName)
{
	CHECKENABLED()

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

	_fileName = fileName;
	try
	{
		HRSOUND(AudioManager::pXAudio2->CreateSourceVoice(&pSourceVoice, reinterpret_cast<WAVEFORMATEX*>(&wfx), 0, XAUDIO2_DEFAULT_FREQ_RATIO, pSourceCallback)); // WARNING: Crashes if no output device is set on the system!
		SetVolume(_volume);
	}
	catch(...)
	{
		_fileName = L"";
	}
}

// **************************** //

COM_DECLSPEC_NOTHROW void AudioManager::AudioSourceCallbacks::OnBufferEnd(void* pBufferContext)
{
	if (source->_ended)
	{
		source->_ended = false;
		return;
	}
	
	source->_playing = false;
	source->_paused = false;
	
	if (!source->_wasPlaying) // if this is false, it means we want to start looping
		return;
	
	source->_wasPlaying = false;
	
	source->Play(); // the callback when a loop ends is OnLoopEnd, so we won't get back here
}

void AudioManager::AudioSourceCallbacks::OnLoopEnd(void* pBufferContext)
{
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

	HRSOUND(pSourceVoice->Start());
	_playing = true;
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
	HRSOUND(Flush());

	_playing = false;
	_paused = false;
}

void AudioSource::Restart()
{
	Stop();
	Play();
}

HRESULT AudioSource::Flush()
{
	if (_hasBuffer)
	{
		HRSOUND(pSourceVoice->FlushSourceBuffers(), AudioManager::hr); // THIS LINE only triggers an end callback IF we flush an UNFINISHED buffer

		if (_playing) // so we're checking that here, and saying "hey, we terminated an unfinished buffer, expect an unnessary callback)
			_ended = true;

		_hasBuffer = false;
	}

	return S_OK;
}

HRESULT AudioSource::Submit()
{
	if (!_hasBuffer)
	{
		HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer), AudioManager::hr);

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
	if (_isLooping == loop)
		return;

	_isLooping = loop;

	CHECKSOURCE()

	UpdateLooping();

	if (_isLooping)
	{
		if (_playing)
			_wasPlaying = true;
	}
	else
	{
		HRSOUND(pSourceVoice->ExitLoop());
		_wasPlaying = false;
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

// **************************** //

float AudioSource::GetVolume()
{
	return _volume;
}

void AudioSource::SetVolume(float volume)
{
	if (volume < MIN_VOLUME)
		volume = MIN_VOLUME;
	else if (volume > MAX_VOLUME)
		volume = MAX_VOLUME;
	
	_volume = volume;

	CHECKSOURCE()

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
