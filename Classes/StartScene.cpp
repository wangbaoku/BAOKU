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

	//创建场景
Scene* StartScene::createScene()
{
		//使用scene的创建方法
	auto scene = Scene::create();
		//创建一个层
	auto layer = StartScene::create();
		//将创建的层放入场景中
	scene->addChild(layer);
		//将创建好的场景返回出去
	return scene;
}

	//初始化
bool StartScene::init()
{
	//调用父类的初始化
	if (!Layer::init())	//如果未初始化
	{
		return false;	//返回
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

	auto size = Director::getInstance()->getWinSize();		//获取窗口大小

	/////////////////////////////////////创建开始场景背景图片////////////////////////////////////////////
	auto startBg = Sprite::create("pic/img_bg_logo.jpg");		//创建开始场景背景图片
	startBg->setAnchorPoint(ccp(0,0));						//设置开始场景背景图片绘制锚点
	startBg->setPosition(ccp(0,0));							//设置开始场景背景图片坐标
	auto starBgSize = startBg->getContentSize();
	startBg->setScale(size.width/starBgSize.width,size.height/starBgSize.height);
	this->addChild(startBg);								//将创建好的背景图片添加到场景中
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////创建logo和光效动画///////////////////////////////////////////////
	auto logo = Sprite::create("pic/logo1.png");			//创建开始场景logo
	logo->setScale(0.8f);									//设置logo的缩放
	Size logoSize = logo->getContentSize();					//获取logo的尺寸
	auto spark = Sprite::create("pic/spark.png");			//创建logo上的光效
	spark->setPosition(-logoSize.width,0);					//设置光效的坐标
	auto clippingNode = ClippingNode::create();				//创建光效的裁剪
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	clippingNode->setPosition(size.width/2,size.height-logoSize.height/2);			//设置裁剪的坐标
#else
	clippingNode->setPosition(size.width/2,size.height-logoSize.height);			//设置裁剪的坐标
#endif
	this->addChild(clippingNode);							//将裁减的节点加入场景中
	clippingNode->setAlphaThreshold(0.05f);					
	clippingNode->setContentSize(logoSize);					//设置裁剪对象
	clippingNode->setStencil(logo);
	clippingNode->addChild(logo,1);
	clippingNode->addChild(spark,2);
	auto moveAction = MoveTo::create(2.0f,Vec2(logoSize.width,0));	//创建光效动画帧
	auto moveBackAction = MoveTo::create(2.0f,Vec2(-logoSize.width,0));//创建光效返回动画帧
	spark->runAction(RepeatForever::create(Sequence::create(moveAction,moveBackAction,NULL)));//让光效执行帧动画
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////创建开始游戏按钮、设置按钮、退出按钮////////////////////////
	auto startbutton = MyButton::CreateButton();	//创建开始游戏按钮
	startbutton->m_init("pic/start.png",CC_CALLBACK_0(StartScene::StartButtonCallBack,this));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	startbutton->setPosition(ccp(size.width/2, size.height/1.6f));
#else
	startbutton->setPosition(ccp(size.width/2, size.height/1.6f));
	startbutton->setScale(1.5f);
#endif
	this->addChild(startbutton);

	auto optionbutton = MyButton::CreateButton();	//创建设置按钮
	optionbutton->m_init("pic/set.png",CC_CALLBACK_0(StartScene::OptionButtonCallBack,this));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	optionbutton->setPosition(ccp(size.width/2, size.height/2.3f));				//设置设置按钮坐标
#else
	optionbutton->setPosition(ccp(size.width/2, size.height/2.3f));				//设置设置按钮坐标
	optionbutton->setScale(1.5f);
#endif
	this->addChild(optionbutton);

	auto quitbutton = MyButton::CreateButton();	//创建退出按钮
	quitbutton->m_init("pic/quit.png",CC_CALLBACK_0(StartScene::QuitButtonCallBack,this));	
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	quitbutton->setPosition(ccp(size.width/2, size.height/3.8f));				//设置退出按钮坐标
#else
	quitbutton->setPosition(ccp(size.width/2, size.height/3.8f));				//设置退出按钮坐标
	quitbutton->setScale(1.5f);
#endif
	this->addChild(quitbutton);

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

	//开始按钮回调函数
void StartScene::StartButtonCallBack()
{
	auto scene = MainScene::createScene();			//创建MainScene场景
	Director::getInstance()->replaceScene(scene);	//替换当前场景
}

	//设置按钮回调函数
void StartScene::OptionButtonCallBack()
{
	auto scene = OptionScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
	
	//退出按钮回调函数
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

