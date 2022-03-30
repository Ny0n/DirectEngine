#pragma once

#define HRSOUND(expression, r)										\
if (FAILED(AudioManager::hr = expression))							\
{																	\
	Utils::PrintError(__FILE__, __LINE__, L"HRSOUND audio error");	\
	Utils::Println(AudioManager::hr);								\
	return r;														\
}1

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

class AudioManager final
{
	friend class Engine;
	friend class AudioSource;

	AudioManager() = default;

	static void Initialize();
	static void Clean();

	// XAudio2 interface
	static IXAudio2* pXAudio2;
	static IXAudio2MasteringVoice* pMasterVoice;

	static HRESULT hr;
	static HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

	// custom voice callback
	class AudioSourceCallbacks : public IXAudio2VoiceCallback
	{

	public:
		virtual ~AudioSourceCallbacks() = default;

		COM_DECLSPEC_NOTHROW void OnVoiceProcessingPassStart(UINT32 BytesRequired) override {}
		COM_DECLSPEC_NOTHROW void OnVoiceProcessingPassEnd() override {}
		COM_DECLSPEC_NOTHROW void OnStreamEnd() override {}
		COM_DECLSPEC_NOTHROW void OnBufferStart(void* pBufferContext) override {}
		COM_DECLSPEC_NOTHROW void OnVoiceError(void* pBufferContext, HRESULT Error) override {}

		// Implemented in AudioSource.cpp
		COM_DECLSPEC_NOTHROW void OnBufferEnd(void* pBufferContext) override;
		COM_DECLSPEC_NOTHROW void OnLoopEnd(void* pBufferContext) override;

		AudioSource* source; // ref to self

	};

};
