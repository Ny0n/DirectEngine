#include "pch.h"

AudioSource::AudioSource()
{
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

	// Sound Player
	
	HRSOUND(AudioManager::pXAudio2->CreateSourceVoice(&pSourceVoice, reinterpret_cast<WAVEFORMATEX*>(&wfx)));

	HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer));
	_hasSetBuffer = true;
}

#define CHECKSOURCE(x)\
if (pSourceVoice == nullptr)\
{\
	Utils::Println("You must set a sound to the Audio Source!");\
	return x;\
}

// **************************** //

void AudioSource::Play()
{
	CHECKSOURCE()

	if (_playing)
		return;

	if (!_hasSetBuffer)
	{
		HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer));
		_hasSetBuffer = true;
	}

	HRSOUND(pSourceVoice->Start());

	_playing = true;
	_paused = false;
}

void AudioSource::Pause()
{
	CHECKSOURCE()

	if (!_playing || _paused)
		return;

	HRSOUND(pSourceVoice->Stop());

	_playing = false;
	_paused = true;
}

void AudioSource::Toggle()
{
	CHECKSOURCE()

	if (!_playing)
		Play();
	else
		Pause();
}

void AudioSource::Stop()
{
	CHECKSOURCE()

	if (_playing)
		HRSOUND(pSourceVoice->Stop());

	HRSOUND(pSourceVoice->FlushSourceBuffers());
	_hasSetBuffer = false;

	_playing = false;
	_paused = false;
}

void AudioSource::Restart()
{
	CHECKSOURCE()

	HRSOUND(pSourceVoice->Stop());
	HRSOUND(pSourceVoice->FlushSourceBuffers());
	HRSOUND(pSourceVoice->SubmitSourceBuffer(&buffer));
	HRSOUND(pSourceVoice->Start());

	_hasSetBuffer = true;
	_playing = true;
	_paused = false;
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
