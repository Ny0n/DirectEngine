#pragma once

class AudioSource : public EngineComponent
{
	string GetType() override { return NAMEOF(AudioSource); }

	void EngineStart() override;
	void EngineUpdate() override;

	void OnEnable() override;
	void OnDisable() override;
	void OnDestroy() override;

public:
	AudioSource();
	explicit AudioSource(LPCWSTR defaultFileName, bool playOnStart = true, float volume = 0.8f, bool isLooping = false);
	~AudioSource() override;

	LPCWSTR GetSound();
	void SetSound(LPCWSTR fileName); // MUST be called before anything else (called by the second constructor in Start)

	void Play();
	void Resume();
	void Pause();
	void Toggle();
	void Stop();
	void Restart();

	bool IsLooping();
	void SetLooping(bool loop); // SetLooping(true) does not start the audio automatically!
	float GetVolume();
	void SetVolume(float volume);

	bool IsPlaying();
	bool IsPaused();

private:
	HANDLE _hFile;

	// sound data
	WAVEFORMATEXTENSIBLE _wfx;
	XAUDIO2_BUFFER _buffer;
	BYTE* _pDataBuffer;

	// sound player
	IXAudio2SourceVoice* _pSourceVoice;

	// custom voice callback
	friend class AudioManager::AudioSourceCallbacks;
	AudioManager::AudioSourceCallbacks* _pSourceCallback;

	LPCWSTR _fileName = L"";
	bool _playOnStart = false;
	float _volume = 0.8f;
	bool _isLooping = false;

	HRESULT Flush();
	HRESULT Submit();
	bool _hasBuffer = false;
	bool _ended = false;

	bool _playing = false;
	bool _paused = false;

	bool _wasPaused = false;
	bool _overrideEnabledCheck = false;

	bool _wasPlaying = false;
	void UpdateLooping();

	float _maxValue = 20.0f;
	float _minValue = 0.0f;
};