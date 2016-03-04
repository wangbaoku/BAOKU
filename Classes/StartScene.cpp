#include "StartScene.h"
#include "Tools.h"
#include "MainScene.h"
#include "Sound.h"
#include "MyButton.h"
#include "OptionScene.h"
#include "ReadFile.h"

StartScene::StartScene(void)
{
}

StartScene::~StartScene(void)
{
}

	//��������
Scene* StartScene::createScene()
{
		//ʹ��scene�Ĵ�������
	auto scene = Scene::create();
		//����һ����
	auto layer = StartScene::create();
		//�������Ĳ���볡����
	scene->addChild(layer);
		//�������õĳ������س�ȥ
	return scene;
}

	//��ʼ��
bool StartScene::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())	//���δ��ʼ��
	{
		return false;	//����
	}

	CReadFile::getInstance()->init();
	if (UserDefault::getInstance()->getBoolForKey("open") == false)
	{
	}
	else
	{
		Sound::getInstance()->setIsPlay(true);
		Sound::getInstance()->playBG("music/1.mp3",true);
	}

	auto size = Director::getInstance()->getWinSize();		//��ȡ���ڴ�С

	/////////////////////////////////////������ʼ��������ͼƬ////////////////////////////////////////////
	auto startBg = Sprite::create("pic/img_bg_logo.jpg");		//������ʼ��������ͼƬ
	startBg->setAnchorPoint(ccp(0,0));						//���ÿ�ʼ��������ͼƬ����ê��
	startBg->setPosition(ccp(0,0));							//���ÿ�ʼ��������ͼƬ����
	auto starBgSize = startBg->getContentSize();
	startBg->setScale(size.width/starBgSize.width,size.height/starBgSize.height);
	this->addChild(startBg);								//�������õı���ͼƬ��ӵ�������
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////����logo�͹�Ч����///////////////////////////////////////////////
	auto logo = Sprite::create("pic/logo1.png");			//������ʼ����logo
	logo->setScale(0.8f);									//����logo������
	Size logoSize = logo->getContentSize();					//��ȡlogo�ĳߴ�
	auto spark = Sprite::create("pic/spark.png");			//����logo�ϵĹ�Ч
	spark->setPosition(-logoSize.width,0);					//���ù�Ч������
	auto clippingNode = ClippingNode::create();				//������Ч�Ĳü�
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	clippingNode->setPosition(size.width/2,size.height-logoSize.height/2);			//���òü�������
#else
	clippingNode->setPosition(size.width/2,size.height-logoSize.height);			//���òü�������
#endif
	this->addChild(clippingNode);							//���ü��Ľڵ���볡����
	clippingNode->setAlphaThreshold(0.05f);					
	clippingNode->setContentSize(logoSize);					//���òü�����
	clippingNode->setStencil(logo);
	clippingNode->addChild(logo,1);
	clippingNode->addChild(spark,2);
	auto moveAction = MoveTo::create(2.0f,Vec2(logoSize.width,0));	//������Ч����֡
	auto moveBackAction = MoveTo::create(2.0f,Vec2(-logoSize.width,0));//������Ч���ض���֡
	spark->runAction(RepeatForever::create(Sequence::create(moveAction,moveBackAction,NULL)));//�ù�Чִ��֡����
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////������ʼ��Ϸ��ť�����ð�ť���˳���ť////////////////////////
	auto startbutton = MyButton::CreateButton();	//������ʼ��Ϸ��ť
	startbutton->m_init("pic/start.png",CC_CALLBACK_0(StartScene::StartButtonCallBack,this));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	startbutton->setPosition(ccp(size.width/2, size.height/1.6f));
#else
	startbutton->setPosition(ccp(size.width/2, size.height/1.6f));
	startbutton->setScale(1.5f);
#endif
	this->addChild(startbutton);

	auto optionbutton = MyButton::CreateButton();	//�������ð�ť
	optionbutton->m_init("pic/set.png",CC_CALLBACK_0(StartScene::OptionButtonCallBack,this));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	optionbutton->setPosition(ccp(size.width/2, size.height/2.3f));				//�������ð�ť����
#else
	optionbutton->setPosition(ccp(size.width/2, size.height/2.3f));				//�������ð�ť����
	optionbutton->setScale(1.5f);
#endif
	this->addChild(optionbutton);

	auto quitbutton = MyButton::CreateButton();	//�����˳���ť
	quitbutton->m_init("pic/quit.png",CC_CALLBACK_0(StartScene::QuitButtonCallBack,this));	
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	quitbutton->setPosition(ccp(size.width/2, size.height/3.8f));				//�����˳���ť����
#else
	quitbutton->setPosition(ccp(size.width/2, size.height/3.8f));				//�����˳���ť����
	quitbutton->setScale(1.5f);
#endif
	this->addChild(quitbutton);

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

	//��ʼ��ť�ص�����
void StartScene::StartButtonCallBack()
{
	auto scene = MainScene::createScene();			//����MainScene����
	Director::getInstance()->replaceScene(scene);	//�滻��ǰ����
}

	//���ð�ť�ص�����
void StartScene::OptionButtonCallBack()
{
	auto scene = OptionScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
	
	//�˳���ť�ص�����
void StartScene::QuitButtonCallBack()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

