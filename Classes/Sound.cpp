#include "Sound.h"
#include "cocos2d.h"

using namespace cocos2d;
static Sound * sound = nullptr;

Sound::Sound(void)
{
	m_isPlay = true;
}

Sound::~Sound(void)
{
}

Sound * Sound::getInstance()
{
	if (nullptr == sound)
	{
		sound = new Sound();
	}
	return sound;

}

void Sound::setIsPlay(bool isPlay)
{
	m_isPlay = isPlay;
	UserDefault::getInstance()->setBoolForKey("open", m_isPlay);
	UserDefault::getInstance()->flush();

}

void Sound::playBG(const char* file, bool isPlay)
{
	isPlay = m_isPlay;
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{// 正在播放
		if (isPlay)
		{// 要求播放

			// 停止当前播放的音乐
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			// 播放新音乐
			SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
		}
		else
		{
			// 停止当前播放的音乐
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	}
	else
	{
		if (isPlay)
		{// 要求播放
			// 播放新音乐
			SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
		}
	}
}

void Sound::preloadEffect(const char* filePath)
{
	SimpleAudioEngine::getInstance()->preloadEffect(filePath);
}

unsigned int Sound::playEffect(const char* filePath)
{
	SimpleAudioEngine::getInstance()->playEffect(filePath);
	return 0;
}

void Sound::stopBackgroundMusic( bool releaseData /*= false*/ )
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

