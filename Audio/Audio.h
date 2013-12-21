//
//

#ifndef AUDIO_H
#define AUDIO_H

// CAudio class
class CAudio //: public IXAudio2VoiceCallback
{
public:
	CAudio();
	~CAudio();

	HRESULT initEngine(); // Initialize the XAudio2 engine

private:
	//IXAudio2 *m_pXAudio;
	//IXAudio2SourceVoice *m_pXAudioSourceVoice;
	//IXAudio2MasteringVoice *m_pXAudioMasteringVoice;

	float m_fVolume;

	HRESULT m_hResult;
};

extern CAudio *g_pAudio;

// Thread for playing sound
DWORD WINAPI playSoundThreadProc(LPVOID lpParam);

#endif // AUDIO_H