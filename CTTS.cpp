#include "stdafx.h"

#include "CTTS.h"

CTTS::CTTS()
{
	startup();
}

CTTS::~CTTS()
{
	shutdown();
}

void CTTS::startup()
{
	// Startup COM
	::CoInitialize(NULL);
	// Open SAPI
	pVoice = NULL;
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	// Set rate and volume
	pVoice->GetRate(&curRate);
	pVoice->GetVolume(&curVolume);
	// Enable processing of XML tags
	XMLProcessing = true;
}

void CTTS::shutdown()
{
	// If a WAV file is open, close it
	closeWAV();
	// Close SAPI
	pVoice->Release();
	pVoice = NULL;
	// Shutdown COM
	::CoUninitialize();
}

void CTTS::reset()
{
	// Reinitialize SAPI
	shutdown();
	startup();
	// Speak a message to inform the user that SAPI has been reinitialized
	speak(L"SAPI Reinitialized.");
}

bool CTTS::isDone()
{
	SPVOICESTATUS status;
	// Get status
	pVoice->GetStatus(&status, NULL);
	if (status.dwRunningState == SPRS_DONE)
	return true;
	else
	return false;
}

bool CTTS::isSpeaking()
{
	SPVOICESTATUS status;
	// Get status
	pVoice->GetStatus(&status, NULL);
	if (status.dwRunningState == SPRS_IS_SPEAKING)
	return true;
	else
	return false;
}

void CTTS::speak(unsigned short *text)
{
	// In case we are paused, call resume
	pVoice->Resume();
	// Speak
	if (XMLProcessing == true)
	pVoice->Speak(text, SPF_ASYNC | SPF_PURGEBEFORESPEAK | SPF_IS_XML, NULL);
	else
	pVoice->Speak(text, SPF_ASYNC | SPF_PURGEBEFORESPEAK | SPF_IS_NOT_XML, NULL);
}

void CTTS::speakToWAV(unsigned short *text, unsigned short *filename)
{
	// Bassed on code from TTSApp sample
	ISpStreamFormat *pOldStream;
	CSpStreamFormat OriginalFmt;
	// If a WAV file is open, close it
	closeWAV();
	// Get the current output stream
	pVoice->GetOutputStream(&pOldStream);
	// Assign format of original stream
	OriginalFmt.AssignFormat(pOldStream);
	// User SAPI helper function in sphelper.h to create a wav file
	if (FAILED(SPBindToFile(filename, SPFM_CREATE_ALWAYS, &pWavStream, &OriginalFmt.FormatId(), OriginalFmt.WaveFormatExPtr())))
	{
		// Display an error if the file couldn't be created
		MessageBox(NULL, _T("WAV file couldn't be created.\n"), _T("Error"), MB_OK | MB_ICONERROR);
		return;
	}
	// Set the voice's output to the wav file instead of the speakers
	pVoice->SetOutput(pWavStream, TRUE);
	// Do the Speak
	speak(text);
	// Wait until the speak is finished if saving to a wav file so that
	// the smart pointer pWavStream doesn't get released before its
	// finished writing to the wav.
	pVoice->WaitUntilDone(INFINITE);
	pWavStream->Close();
	// Reset output
	pVoice->SetOutput(pOldStream, FALSE);
	// Let the user know that the file has been created
	MessageBox(NULL, _T("WAV file created.\n"), _T("Information"), MB_OK | MB_ICONINFORMATION);
}

void CTTS::playWAV(unsigned short *filename)
{
	// Bassed on code from TTSApp sample
	// If a WAV file is open, close it
	closeWAV();
	// User helper function found in sphelper.h to open the wav file and
	// get back an IStream pointer to pass to SpeakStream
	if (SUCCEEDED(SPBindToFile(filename, SPFM_OPEN_READONLY, &pWavStream)))
	{
		// If we successfully opened the file, set WAVOpen to true
		WAVOpen = true;
	}
	// In case we are paused, call resume
	pVoice->Resume();
	// Speak stream
	pVoice->SpeakStream(pWavStream, SPF_ASYNC | SPF_PURGEBEFORESPEAK, NULL);
}

void CTTS::closeWAV()
{
	if (WAVOpen == true)
	{
		// If a WAV file is open, close the stream and set WAVOpen to false
		pWavStream->Close();
		WAVOpen = false;
	}
}

void CTTS::pauseResume()
{
	// If we are speaking, call pause
	// If we are not speaking, call resume
	if (isSpeaking())
	pVoice->Pause();
	else
	pVoice->Resume();
}

void CTTS::stop()
{
	// Speak a null string
	speak(NULL);
}

void CTTS::rateUp()
{
	// Increment curRate
	curRate++;
	// Set the new rate
	pVoice->SetRate(curRate);
	// Inform the user that the rate is faster
	speak(L"Faster.");
}

void CTTS::rateDown()
{
	// Decrement curRate
	curRate--;
	// Set the new rate
	pVoice->SetRate(curRate);
	// Inform the user that the rate is slower
	speak(L"Slower.");
}

void CTTS::volumeUp()
{
	// Increment curVolume
	curVolume++;
	// Set the new volume
	pVoice->SetVolume(curVolume);
	// Inform the user that the volume is louder
	speak(L"Louder.");
}

void CTTS::volumeDown()
{
	// Decrement curVolume
	curVolume--;
	// Set the new volume
	pVoice->SetVolume(curVolume);
	// Inform the user that the volume is quieter
	speak(L"Quieter.");
}

void CTTS::setXMLProcessing(bool value)
{
	XMLProcessing = value;
}

bool CTTS::getXMLProcessing()
{
	return XMLProcessing;
}

void CTTS::rewind(signed long numItems)
{
	// Move back by the specified number of items
	pVoice->Skip(L"Sentence", numItems*-1, NULL);
}

void CTTS::fastForward(signed long numItems)
{
	// Move forward by the specified number of items
	pVoice->Skip(L"Sentence", numItems, NULL);
}
