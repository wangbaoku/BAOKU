#include "OptionScene.h"
#include "Sound.h"
#include "StartScene.h"

OptionScene::OptionScene(void)
{
	m_Effect = true;
}


OptionScene::~OptionScene(void)
{
}

Scene* OptionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool OptionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("pic/ui_loading_Background.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	bg->setScale(visibleSize.width/bg->getContentSize().width,visibleSize.height/bg->getContentSize().height);
	this->addChild(bg);

	kuang1 = Sprite::create("pic/selected01.png");
	kuang1->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height / 2.0f));
	this->addChild(kuang1);

	auto kuang1lable = Sprite::create("pic/music.png");
	kuang1lable->setPosition(kuang1->getPositionX(),
		kuang1->getPositionY() - kuang1lable->getContentSize().height - kuang1->getContentSize().height/2);
	this->addChild(kuang1lable);

	kuang2 = Sprite::create("pic/selected01.png");
	kuang2->setPosition(Vec2(visibleSize.width * 0.7f, visibleSize.height / 2.0f));
	this->addChild(kuang2);

	auto kuang2lable = Sprite::create("pic/effect.png");
	kuang2lable->setPosition(kuang2->getPositionX(),
		kuang2->getPositionY() - kuang2->getContentSize().height/2 - kuang2lable->getContentSize().height);
	this->addChild(kuang2lable);

	sound_selected = Sprite::create("pic/selected02.png");
	sound_selected->setPosition(kuang1->getPosition());
	if (UserDefault::getInstance()->getBoolForKey("open") == true)
	{
		this->addChild(sound_selected);
	}

	effect_selected = Sprite::create("pic/selected02.png");
	effect_selected->setPosition(kuang2->getPosition());
	if(UserDefault::getInstance()->getBoolForKey("Effect") == true)
	{
		this->addChild(effect_selected);
	}

	auto backButton = MyButton::CreateButton();
	backButton->m_init("pic/back.png",CC_CALLBACK_1(OptionScene::backButtonCallback,this));
	backButton->setPosition(visibleSize.width * 0.5,visibleSize.height * 0.25);
	this->addChild(backButton);

	auto size = Director::getInstance()->getWinSize();		//获取窗口大小
	{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("pic/Hero.ExportJson");
		m_pAr1 = Armature::create("Hero");
		m_pAr1->getAnimation()->play("run");
		m_pAr1->setPosition(ccp(size.width * 0.3f,size.height * 0.8f));
		this->addChild(m_pAr1);
	}
	{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("pic/Hero2.ExportJson");
		m_pAr2 = Armature::create("Hero2");
		m_pAr2->getAnimation()->play("run");
		m_pAr2->setPosition(ccp(size.width * 0.7f,size.height * 0.78f));
		this->addChild(m_pAr2);
	}

	plane_selected = Sprite::create("pic/selected02.png");
	if (UserDefault::getInstance()->getIntegerForKey("index") == 0)
	{
		plane_selected->setPosition(m_pAr1->getPositionX(), m_pAr1->getPositionY());
	}
	if (UserDefault::getInstance()->getIntegerForKey("index") == 1)
	{
		plane_selected->setPosition(m_pAr2->getPositionX(), m_pAr2->getPositionY());
	}
	this->addChild(plane_selected);
	/////////////////////////////////创建触摸键听事件//////////////////////////////////////////////////
	EventListenerTouchOneByOne * m_touchListener = EventListenerTouchOneByOne::create();	//创建单点触控监听
	m_touchListener->onTouchBegan = CC_CALLBACK_2(OptionScene::onTouchBegan,this);			//绑定onTouchBegan
	m_touchListener->setSwallowTouches(true);		//设置吞噬触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener,this);	//注册监听
	return true;
}

void OptionScene::backButtonCallback( cocos2d::Ref* pSender )
{
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool OptionScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	auto point = touch->getLocation();		//获取点击的位置
	auto rect1 = m_pAr1->getBoundingBox();
	auto rect2 = m_pAr2->getBoundingBox();
	auto kuang1box = kuang1->getBoundingBox();
	auto kuang2box = kuang2->getBoundingBox();
	if (rect1.containsPoint(point))	
	{
		setIndex(0);
		auto pos = m_pAr1->getPosition();
		plane_selected->setPosition(pos);
	}
	if (rect2.containsPoint(point))
	{
		setIndex(1);
		auto pos = m_pAr2->getPosition();
		plane_selected->setPosition(pos);
	}
	if (kuang1box.containsPoint(point))
	{
		if (UserDefault::getInstance()->getBoolForKey("open") == false)
		{
			Sound::getInstance()->setIsPlay(true);
			Sound::getInstance()->playBG("music/1.mp3",true);
			sound_selected = Sprite::create("pic/selected02.png");
			sound_selected->setPosition(kuang1->getPosition());
			this->addChild(sound_selected);
		}
		else if(UserDefault::getInstance()->getBoolForKey("open") == true)
		{
			Sound::getInstance()->setIsPlay(false);	
			Sound::getInstance()->stopBackgroundMusic(true);
			sound_selected->removeFromParent();
		}
	}
	if (kuang2box.containsPoint(point))
	{
		if(UserDefault::getInstance()->getBoolForKey("Effect") == false)
		{
			m_Effect = true;
			UserDefault::getInstance()->setBoolForKey("Effect",m_Effect);
			UserDefault::getInstance()->flush();
			effect_selected = Sprite::create("pic/selected02.png");
			effect_selected->setPosition(kuang2->getPosition());
			this->addChild(effect_selected);
		}
		else if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
		{
			m_Effect = false;
			UserDefault::getInstance()->setBoolForKey("Effect",m_Effect);
			UserDefault::getInstance()->flush();
			effect_selected->removeFromParent();
		}
	}
	return false;
}

void OptionScene::setIndex( int index )
{
	UserDefault::getInstance()->setIntegerForKey("index",index);
	UserDefault::getInstance()->flush();

}

