#if !defined(CTTS_H)
#define CTTS_H

#include <sapi.h>

class CTTS
{
protected:
	HRESULT hr;
	ISpVoice * pVoice;
public:
	CTTS();
	~CTTS();
	bool isSpeaking();
	void speak(unsigned short *text);
	void pause();
	void stop();
};

#endif // !defined(CTTS_H)
