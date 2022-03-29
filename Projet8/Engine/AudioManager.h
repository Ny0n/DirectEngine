#pragma once

#define HRSOUND(expression)											\
if (FAILED(AudioManager::hr = expression))							\
{																	\
	Utils::PrintError(__FILE__, __LINE__, L"HRSOUND audio error");	\
	Utils::Println(AudioManager::hr);								\
	return;															\
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

};
