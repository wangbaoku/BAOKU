#pragma once
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class Sound
{
public:
	void playBG(const char* file, bool isPlay);
	void setIsPlay(bool isPlay);
	bool getIsPlay(){return m_isPlay;};
	static Sound * getInstance();
	void preloadEffect(const char* filePath);
	unsigned int playEffect(const char* filePath);
	void stopBackgroundMusic(bool releaseData = false);

protected:



private:
	Sound(void);
	~Sound(void);
	bool m_isPlay;
};

