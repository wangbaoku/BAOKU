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
	{// ���ڲ���
		if (isPlay)
		{// Ҫ�󲥷�

			// ֹͣ��ǰ���ŵ�����
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			// ����������
			SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
		}
		else
		{
			// ֹͣ��ǰ���ŵ�����
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	}
	else
	{
		if (isPlay)
		{// Ҫ�󲥷�
			// ����������
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

