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

void CTTS::speakToWAV(unsigned short *text, unsigned short *filename)
{
	//bassed on code from TTSApp sample
	ISpStream *pWavStream;
	ISpStreamFormat *pOldStream;
	CSpStreamFormat OriginalFmt;
	if (isSpeaking())
	{
		return;
	}
	// Get the current output stream
	hr = pVoice->GetOutputStream(&pOldStream);
	if (hr == S_OK)
	{
		// Assign format of original stream
		hr = OriginalFmt.AssignFormat(pOldStream);
	}
	else
	{
		hr = E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// User SAPI helper function in sphelper.h to create a wav file
		hr = SPBindToFile(filename, SPFM_CREATE_ALWAYS, &pWavStream, &OriginalFmt.FormatId(), OriginalFmt.WaveFormatExPtr());
	}
	if (SUCCEEDED(hr))
	{
		// Set the voice's output to the wav file instead of the speakers
		hr = pVoice->SetOutput(pWavStream, TRUE);
	}
	if (SUCCEEDED(hr))
	{
		// Do the Speak
		hr = pVoice->Speak(text, SPF_ASYNC, NULL);
	}
	// Wait until the speak is finished if saving to a wav file so that
	// the smart pointer cpWavStream doesn't get released before its
	// finished writing to the wav.
	pVoice->WaitUntilDone(INFINITE);
	if (SUCCEEDED(hr))
	{
		// close the stream
		hr = pWavStream->Close();
	}
	// Reset output
	pVoice->SetOutput(pOldStream, FALSE);
	MessageBox(NULL, _T("WAV file created.\n"), _T("Information"), MB_OK | MB_ICONINFORMATION);
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
