#include "stdafx.h"

#include "CTTS.h"

CTTS::CTTS()
{
	::CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
}

CTTS::~CTTS()
{
	pVoice->Release();
	pVoice = NULL;
	::CoUninitialize();
}

bool CTTS::isSpeaking()
{
	SPVOICESTATUS status;
	if( SUCCEEDED( hr ) )
	{
		hr = pVoice->GetStatus(&status, NULL);
		if (status.dwRunningState == SPRS_IS_SPEAKING)
		return true;
	}
	return false;
}

void CTTS::speak(unsigned short *text)
{
	if( SUCCEEDED( hr ) )
	{
		if (isSpeaking())
		return;
		else
		hr = pVoice->Speak(text, SPF_ASYNC, NULL);
	}
}

void CTTS::pause()
{
	if( SUCCEEDED( hr ) )
	{
		if (isSpeaking())
		hr = pVoice->Pause();
		else
		hr = pVoice->Resume();
	}
}

void CTTS::stop()
{
	if( SUCCEEDED( hr ) )
	{
		hr = pVoice->Speak(NULL, SPF_ASYNC | SPF_PURGEBEFORESPEAK, NULL);
	}
}
