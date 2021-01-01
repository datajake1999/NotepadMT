#if !defined(CTTS_H)
#define CTTS_H

#include <sapi.h>
#include <sphelper.h>

class CTTS
{
protected:
	ISpVoice * pVoice;
	ISpStream * pWavStream;
	signed long curRate;
	unsigned short curVolume;
	bool WAVOpen;
	bool XMLProcessing;
	void startup();
	void shutdown();
	void closeWAV();
public:
	CTTS();
	~CTTS();
	void reset();
	bool isDone();
	bool isSpeaking();
	void speak(unsigned short *text);
	void speakToWAV(unsigned short *text, unsigned short *filename);
	void playWAV(unsigned short *filename);
	void pauseResume();
	void stop();
	void rateUp();
	void rateDown();
	void volumeUp();
	void volumeDown();
	void setXMLProcessing(bool value);
	bool getXMLProcessing();
	void rewind(signed long numItems);
	void fastForward(signed long numItems);
};

#endif // !defined(CTTS_H)
