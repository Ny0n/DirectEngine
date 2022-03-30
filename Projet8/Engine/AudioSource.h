#pragma once

class AudioSource : public EngineComponent
{
	string GetType() override { return NAMEOF(AudioSource); }

	void EngineStart() override;
	void EngineUpdate() override;

public:
	AudioSource();
	~AudioSource() override;

	void SetSound(LPCWSTR fileName);

	void Play();
	void Resume();
	void Pause();
	void Toggle();
	void Stop();
	void Restart();

	void Testing();

	bool IsLooping();
	void SetLooping(bool loop); // SetLooping(true) does not start the audio automatically!
	float GetVolume();
	void SetVolume(float volume);

	bool IsPlaying();
	bool IsPaused();

private:
	// sound data
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
	bool _hasSetBuffer = false;

	// sound player
	IXAudio2SourceVoice* pSourceVoice;

	// custom voice callback
	friend class AudioManager::AudioSourceCallbacks;
	AudioManager::AudioSourceCallbacks* pSourceCallback;

	HRESULT Flush();
	HRESULT Submit();
	bool _hasBuffer = false;
	bool _ended = false;
	bool _restarting = false;

	bool _playing = false;
	bool _paused = false;

	bool _isLooping = false;
	bool _wasPlaying = false;
	void UpdateLooping();

	float MAX_VOLUME = 20.0f;
	float MIN_VOLUME = 0.0f;

};
