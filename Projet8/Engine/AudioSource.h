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
	void Flush();

	void Play();
	void Pause();
	void Toggle();
	void Stop();
	void Restart();

	float GetVolume();
	void SetVolume(float volume);

	bool IsPlaying();
	bool IsPaused();

private:
	// sound data
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// sound player
	IXAudio2SourceVoice* pSourceVoice;

	bool _playing = false;
	bool _paused = false;

	bool _hasSetBuffer = false;

	float MAX_VOLUME = 20.0f;
	float MIN_VOLUME = 0.0f;

};
