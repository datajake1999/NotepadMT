#if !defined(CTTS_H)
#define CTTS_H

#include <sapi.h>
#include <sphelper.h>

class CTTS
{
protected:
	HRESULT hr;
	ISpVoice * pVoice;
public:
	CTTS();
	~CTTS();
	bool isDone();
	bool isSpeaking();
	void speak(unsigned short *text);
	void speakToWAV(unsigned short *text, unsigned short *filename);
	void playWAV(unsigned short *filename);
	void pause();
	void stop();
};

#endif // !defined(CTTS_H)
