#include "MyButton.h"
#include "Sound.h"

MyButton::MyButton(void)
{
}

MyButton::~MyButton(void)
{
}

	//创建按钮
MyButton* MyButton::CreateButton()
{
	auto button = MyButton::create();
	return button;
}
	
	//初始化
bool MyButton::init()
{
	if (!Node::init())
	{
		return false;
	}
	Sound::getInstance()->preloadEffect("music/button.wav");
	return true;
}

	//按钮功能
void MyButton::m_init(string name,const ccMenuCallback _CallBack)
{
	m_Name=name;
	m_callback=_CallBack;

	this->initWithFile(m_Name);

	auto dir = Director::getInstance()->getEventDispatcher();
	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = 
		[=](Touch* pTouch, Event* pEvent)->bool{
		Vec2 pos = pTouch->getLocation();
		if (this->getBoundingBox().containsPoint(pos))
		{
			if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
			{
				Sound::getInstance()->playEffect("music/button.wav");
			}
			#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			this->setScale(0.8f);
			#else
			this->setScale(1.3f);
			#endif
			return true;

		}
		return false;
	};
	touch->onTouchEnded = [=](Touch* pTouch, Event* pEvent){
		Vec2 pos = pTouch->getLocation();
		if (this->getBoundingBox().containsPoint(pos))
		{
			#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			this->setScale(1.0f);
			#else
			this->setScale(1.5f);
			#endif
			m_callback(this);

		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch,this);

}

