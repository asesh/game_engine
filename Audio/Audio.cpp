//
//

#include "..\Common\StdAfx.h"
#include "Audio.h"

//--------------------------------------------------------
// Name: CAudio
// Desc: Default constructor
//--------------------------------------------------------
CAudio::CAudio()
{
	//m_pXAudio = NULL;
	//m_pXAudioSourceVoice = NULL;
	//m_pXAudioMasteringVoice = NULL;
}

//--------------------------------------------------------
// Name: ~CAudio
// Desc: Destructor
//--------------------------------------------------------
CAudio::~CAudio()
{
	//RELEASE_COM(m_pXAudioMasteringVoice);
	//FREE_COM(m_pXAudio);

	// Uninitialize the COM library
	::CoUninitialize();
}

//--------------------------------------------------------
// Name: initEngine
// Desc: Initialize the XAudio2 engine
//--------------------------------------------------------
HRESULT CAudio::initEngine()
{
	UINT32 uiAudioDevicesCount;

	// Initialize the COM library
	//CHECK_COM(::CoInitializeEx(NULL, COINIT_MULTITHREADED));

	// Create
	//CHECK_COM(::XAudio2Create(&m_pXAudio, 0, XAUDIO2_ANY_PROCESSOR));

	//// Get the number of audio devices installed on the system
	//CHECK_COM(m_pXAudio->GetDeviceCount(&uiAudioDevicesCount));

	//// Prepare XAudio2 for use
	//CHECK_COM(m_pXAudio->Initialize(0, XAUDIO2_DEFAULT_PROCESSOR));

	//// Create and configure a mastering voice
	//CHECK_COM(m_pXAudio->CreateMasteringVoice(&m_pXAudioMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL));

	return S_OK;
}

//--------------------------------------------------------
// Name: playSoundThreadProc
// Desc: Thread procedure for playing sound
//--------------------------------------------------------
DWORD WINAPI playSoundThreadProc(LPVOID lpParam)
{
	return 0;
}

//CAudio g_oAudio;
//CAudio *g_pAudio = &g_oAudio;