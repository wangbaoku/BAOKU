#include "MainScene.h"
#include "StartScene.h"
#include "Control.h"
#include "Tools.h"
#include "MyButton.h"
#include "EnemyBoss.h"
#include "Sound.h"
#include "ReadFile.h"
#include "bomEff.h"
MainScene::MainScene(void)
	: m_pAr(nullptr),
	Hp_Label_num(nullptr)
{
}

MainScene::~MainScene(void)
{
}

Scene* MainScene::createScene()
{
	//ʹ��scene�Ĵ�������
	auto scene = Scene::create();
	//����һ����
	auto layer = MainScene::create();
	//�������Ĳ���볡����
	scene->addChild(layer);
	//�������õĳ������س�ȥ
	return scene;
}
	
bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Sound::getInstance()->preloadEffect("music/bullet.wav");
	Sound::getInstance()->preloadEffect("music/bom.wav");
	score = 0;
	time = 0;
	speed = 1;
	Size visibleSize = Director::getInstance()->getVisibleSize();	//��ȡ��������Ĵ�С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();		//��ȡ�߼�����Ĵ�С
	////////////////////////////////////////����������ͼ///////////////////////////////////////////////
	bg1 = Sprite::create("pic/img_bg_level_2.jpg");			//������һ�ű���ͼƬ
	auto bg1size = bg1->getContentSize();			//��ȡ��һ�ű���ͼƬ�ߴ�
	bg1->setScale(visibleSize.width/bg1size.width, visibleSize.height/bg1size.height);	//���ñ���ͼƬΪȫ��
	bg1->setPosition(0,0);
	bg1->setAnchorPoint(Vec2(0,0));
	this->addChild(bg1);
	bg2 = Sprite::create("pic/img_bg_level_2.jpg");			//�����ڶ��ű���ͼƬ
	auto bg2size = bg2->getContentSize();			//��ȡ�ڶ��ű���ͼƬ�ߴ�
	bg2->setScale(visibleSize.width/bg1size.width, visibleSize.height/bg1size.height);	//����Ϊȫ��
	bg2->setPosition(0,visibleSize.height);
	bg2->setAnchorPoint(Vec2(0,0));
	this->addChild(bg2);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	initHeroPlane();
	///////////////////////////////////������Ϸ������ͣ��ť////////////////////////////////////////////
	auto pausebutton = MyButton::CreateButton();	//������ͣ��Ϸ��ť
	pausebutton->m_init("pic/uiPause.png",CC_CALLBACK_0(MainScene::AddPauseLayer,this));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	pausebutton->setPosition(visibleSize.width-22,visibleSize.height-22);
#else
	pausebutton->setPosition(visibleSize.width-22,visibleSize.height-22);
	pausebutton->setScale(1.5f);
#endif
	this->addChild(pausebutton);


	///////////////////////////////////////���ը����ť////////////////////////////////////////////////
	auto bom = MyButton::CreateButton();
	bom->m_init("pic/bom.png",CC_CALLBACK_0(MainScene::bomClear,this));
	auto bomSize = bom->getContentSize();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	bom->setPosition(bomSize.width/2,visibleSize.height * 0.3f);
#else
	bom->setPosition(bomSize.width/2,visibleSize.height * 0.3f);
	bom->setScale(1.5f);
#endif
	this->addChild(bom);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////�������������¼�//////////////////////////////////////////////////
	
	EventListenerTouchOneByOne * m_touchListener = EventListenerTouchOneByOne::create();	//�������㴥�ؼ���
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);			//��onTouchBegan
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved,this);			//��onTouchMoved
	m_touchListener->setSwallowTouches(true);		//�������ɴ���
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener,this);	//ע�����

	//---------------------------------���÷���------------------------------------------------
	//��������
	auto size = Director::getInstance()->getWinSize();		//��ȡ���ڴ�С
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto label_score = Label::create(Tools::Unicode2Utf8(L"��ǰ��"),"fonts/msyh.ttc",24);
#else
	string dangqianfen = "��ǰ��";
	Tools::GBKToUTF8(dangqianfen);
	auto label_score = Label::create(dangqianfen,"fonts/msyh.ttc",24);
#endif
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(label_score->getContentSize().width / 2 + 5, size.height - label_score->getContentSize().height / 2 - 5));
	this->addChild(label_score,100);

	label_score_num_ = Label::create();
	label_score_num_->setSystemFontSize(24);
	label_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_score_num_->setPosition(ccp(label_score->getContentSize().width + 5, label_score->getPositionY()));
	this->addChild(label_score_num_,100);
	//��߷�
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto label_best_score = Label::create(Tools::Unicode2Utf8(L"��߷�"),"fonts/msyh.ttc",24);
#else
	string zuigaofen = "��߷�";
	Tools::GBKToUTF8(zuigaofen);
	auto label_best_score = Label::create(zuigaofen,"fonts/msyh.ttc",24);
#endif
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(label_best_score->getContentSize().width / 2 + 5, label_score->getPositionY() - label_best_score->getContentSize().height - 5));
	this->addChild(label_best_score,100);

	label_best_score_num_ = Label::create();
	label_best_score_num_->setSystemFontSize(24);
	label_best_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num_->setPosition(ccp(label_best_score->getContentSize().width + 5, label_best_score->getPositionY()));
	this->addChild(label_best_score_num_,100);

	//��߷�
	int score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	label_best_score_num_->setString(String::createWithFormat("%d", score_win)->getCString());
	//��ǰ��
	label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
	//-----------------------------------------------end-------------------------------------------------------
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto Hp_Label = Label::create(Tools::Unicode2Utf8(L"Ѫ��"),"fonts/msyh.ttc",24);
#else
	string hp = "Ѫ��";
	Tools::GBKToUTF8(hp);
	auto Hp_Label = Label::create(hp,"fonts/msyh.ttc",24);
#endif
	Hp_Label->setAnchorPoint(ccp(0.5, 0.5));
	Hp_Label->setPosition(ccp(Hp_Label->getContentSize().width / 2 + 5, label_best_score->getPositionY() - Hp_Label->getContentSize().height - 5));
	this->addChild(Hp_Label,100);

	Hp_Label_num = Label::create();
	Hp_Label_num->setSystemFontSize(24);
	Hp_Label_num->setAnchorPoint(ccp(0, 0.5));
	Hp_Label_num->setPosition(ccp(Hp_Label->getContentSize().width + 5, Hp_Label->getPositionY()));
	this->addChild(Hp_Label_num,100);
	Hp_Label_num->setString(String::createWithFormat("%d", Hero_Plane_Hp)->getCString());
	return true;
}
		
void MainScene::onEnterTransitionDidFinish()			
{
	Layer::onEnterTransitionDidFinish();	
	this->schedule(SEL_SCHEDULE(&MainScene::bg1Move));				//��ͼ����
	this->schedule(SEL_SCHEDULE(&MainScene::addBullet),0.1f);		//����ӵ�
	this->schedule(SEL_SCHEDULE(&MainScene::is_crash));				//��ײ���
	this->schedule(SEL_SCHEDULE(&MainScene::addEnemy),CReadFile::getInstance()->getEnemyTime());		//��ӵл�
	this->schedule(SEL_SCHEDULE(&MainScene::addBullet2),1.5f);		//��ӵл��ӵ�
}

void MainScene::onExit()
{
	unscheduleUpdate();		//ֹͣ����
	Layer::onExit();
}
	
void MainScene::bg1Move( float delta )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	///////////////////////////////ʵ�ֵ�ͼ����///////////////////////////////////////////
	bg1->setPositionY(bg1->getPositionY()-speed);		
	if (bg1->getPositionY() <= -visibleSize.height)
	{
		bg1->setPositionY(visibleSize.height);
	}
	bg2->setPositionY(bg2->getPositionY()-speed);
	if (bg2->getPositionY() <= -visibleSize.height)
	{
		bg2->setPositionY(visibleSize.height);
	}
	/////////////////////////////////////////////////////////////////////////////////////

}

bool MainScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	auto point = touch->getLocation();		//��ȡ�����λ��
	auto rect = m_pAr->getBoundingBox();//��ȡ���Ƿɻ��ľ���
	if (rect.containsPoint(point))	
	{
		return true;
	}
	return false;
}

void MainScene::initHeroPlane()
{
	if (m_pAr)
	{
		m_pAr->removeFromParentAndCleanup(true);
	}
	Hero_Plane_Hp = 100;
	auto size = Director::getInstance()->getWinSize();		//��ȡ���ڴ�С
	if (UserDefault::getInstance()->getIntegerForKey("index",index) == 0)
	{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("pic/Hero.ExportJson");
		m_pAr = Armature::create("Hero");
		m_pAr->getAnimation()->play("run");
		m_pAr->setName("Hero_Plane");
		m_pAr->setPosition(ccp(size.width/2,size.height * 0.2));
		this->addChild(m_pAr);
	}
	if (UserDefault::getInstance()->getIntegerForKey("index",index) == 1)
	{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("pic/Hero2.ExportJson");
		m_pAr = Armature::create("Hero2");
		m_pAr->getAnimation()->play("run");
		m_pAr->setName("Hero_Plane");
		m_pAr->setPosition(ccp(size.width/2,size.height * 0.2));
		this->addChild(m_pAr);
	}
	x = Sprite::create("pic/x.png");
	x->setPosition(m_pAr->getPositionX(),m_pAr->getPositionY());
	x->setName("x");
	m_pAr->addChild(x);

}

void MainScene::onTouchMoved( Touch *touch, Event *unused_event )
{
	auto add_point = touch->getLocation() - touch->getPreviousLocation();	//��ȡ�ɻ����ƶ�����
	m_pAr->setPosition(m_pAr->getPosition() + add_point);
	x->setPosition(m_pAr->getPosition());
	auto size = Director::getInstance()->getWinSize();	//��ȡ���ڴ�С
	auto Hero_Size = m_pAr->getContentSize();		//��ȡ���Ƿɻ���С
	//�жϲ��ܷɳ��߿�
	if (m_pAr->getPositionX() < Hero_Size.width/2)	
	{
		m_pAr->setPositionX(Hero_Size.width/2);
	}
	else if(m_pAr->getPositionX() > size.width - Hero_Size.width/2)
	{
		m_pAr->setPositionX(size.width - Hero_Size.width/2);
	}
	if (m_pAr->getPositionY() < Hero_Size.height/2)	
	{
		m_pAr->setPositionY(Hero_Size.height / 2);
	}
	else if(m_pAr->getPositionY() > size.height - Hero_Size.height/2)
	{
		m_pAr->setPositionY(size.height - Hero_Size.height/2);
	}
}

void MainScene::setHeroPlaneHp()
{
	Hero_Plane_Hp--;
}

void MainScene::addEnemy( float dt )
{
	int enemy_x = CCRANDOM_0_1() * 9 + 1;	//ʹ��������ɵл�
	if (enemy_x > 4)
	{
		enemy_x = 2;
	}
	else
	{
		enemy_x = 1;
	}

	auto enemy = Enemy::create();	//�����л�
	enemy->initEnemy(enemy_x);
	this->addChild(enemy);
	Control::getInstance()->setEnemyList(enemy);	//���л�������ƶ���
}

void MainScene::addEnemyBoss(int enemyBossHp)
{
	auto enemyBoss = EnemyBoss::create();
	enemyBoss->initEnemyBoss(1);
	enemyBoss->set_hp(enemyBossHp);
	this->addChild(enemyBoss);
	Control::getInstance()->setEnemyBossList(enemyBoss);
}

void MainScene::addBullet( float )
{
	bullet = Bullet::create();		//�����ӵ�
	bullet->initBullet(BULLET_1);
	auto point = ccp(m_pAr->getPositionX(),m_pAr->getPositionY()+m_pAr->getContentSize().height/2 + 5);
	bullet->setPosition(point);
	this->addChild(bullet);
	Control::getInstance()->setBulletList(bullet);	//���ӵ�������ƶ���
	if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
	{
		Sound::getInstance()->playEffect("music/bullet.wav");
	}
	
}

void MainScene::addBullet1(float dt)
{
	{
		auto bullet1 = Bullet::create();
		bullet1->initBullet(BULLET_1);
		auto point = Point(m_pAr->getPositionX()-10,
			m_pAr->getPositionY() + m_pAr->getContentSize().height / 2 + 10);
		bullet1->setPosition(point);
		this->addChild(bullet1);
		if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
		{
			Sound::getInstance()->playEffect("music/bullet.wav");
		}
		Control::getInstance()->setBulletList(bullet1);
	}

	{
		auto bullet2 = Bullet::create();
		bullet2->initBullet(BULLET_1);
		auto point = Point(m_pAr->getPositionX()+10,
			m_pAr->getPositionY() + m_pAr->getContentSize().height / 2 + 10);
		bullet2->setPosition(point);
		this->addChild(bullet2);
		if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
		{
			Sound::getInstance()->playEffect("music/bullet.wav");
		}
		Control::getInstance()->setBulletList(bullet2);
	}
}

void MainScene::addBullet2( float dt )
{
	auto & enemy_list = Control::getInstance()->getEnemyList();	//��ȡ�л�����
	for (int i = enemy_list.size() - 1; i >= 0; --i)	//ʹ�õ�������л�����
	{
		auto enemy = enemy_list.at(i);
		if (enemy->getPositionY() > Director::getInstance()->getWinSize().height/2)
		{		
			auto bullet1 = Bullet::create();
			bullet1->initBullet(BULLET_2);
			auto point = ccp(enemy->getPositionX(),enemy->getPositionY()+enemy->getContentSize().height/2);
			bullet1->setPosition(point);
			bullet1->setScale(0.5f);
			this->addChild(bullet1);
			Control::getInstance()->setEnemyBulletList(bullet1);
		}
	}

}

void MainScene::addBullet3(float dt)
{
	{
		auto bullet = Bullet::create();
		bullet->initBullet(BULLET_3);
		auto point = Point(m_pAr->getPositionX()+40,
			m_pAr->getPositionY() + m_pAr->getContentSize().height / 2 + 10);
		bullet->setPosition(point);
		this->addChild(bullet);
		Control::getInstance()->setBulletList(bullet);
	}

	{
		auto bullet = Bullet::create();
		bullet->initBullet(BULLET_3);
		auto point = Point(m_pAr->getPositionX()-40,
			m_pAr->getPositionY() + m_pAr->getContentSize().height / 2 + 10);
		bullet->setPosition(point);
		this->addChild(bullet);
		Control::getInstance()->setBulletList(bullet);
	}

}	

void MainScene::is_crash( float tm )
{
	time++;
	auto & enemy_list = Control::getInstance()->getEnemyList();	//��ȡ�л�����
	auto & bullet_list = Control::getInstance()->getBulletList();	//��ȡ�ӵ�����
	auto & enemy_bullet_list = Control::getInstance()->getEnemyBulletList();//��ȡ�л��ӵ�����
	auto & enemy_boss_list = Control::getInstance()->getEnemyBossList();	//��ȡ�л�BOSS����
	for (int i = enemy_list.size() - 1; i >= 0; --i)	//ʹ�õ�������л�����
	{
		auto enemy = enemy_list.at(i);
		auto enemy_size = enemy->getBoundingBox();	//��ȡ�л��ľ���
		for (int i = bullet_list.size()-1; i >= 0; --i)	//ʹ�õ�������ӵ�����
		{
			auto bullet = bullet_list.at(i);
			if (enemy_size.containsPoint(bullet->getPosition()))	//���ӵ��������ڵл��ľ�����
			{
				Control::getInstance()->removeBulletList(bullet);	//�����������ӵ�
				bullet->removeFromParentAndCleanup(true);
					auto bomeff = bomEff::create();
					this->addChild(bomeff);
					bomeff->playBomEff(enemy->getPosition());
					enemy->EnemyDeath();		//���õл���ը����
					if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
					{
						Sound::getInstance()->playEffect("music/bom.wav");
					}
					score += 10;
					if (score >= 200)
					{
						this->unschedule(SEL_SCHEDULE(&MainScene::addBullet));
						this->schedule(SEL_SCHEDULE(&MainScene::addBullet1),0.1f);
					}
					if (score >= 500)
					{
						this->schedule(SEL_SCHEDULE(&MainScene::addBullet3),1.0f);
					}
					label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
					break;
			}
		}
	}
	
	//�л�������
	for (int i = enemy_list.size()-1; i >= 0; --i)	//ʹ�õ�������л�����
	{
		auto enemy = enemy_list.at(i);
		auto rect = enemy->getBoundingBox();		//��ȡ�л��ľ���
		auto point = this->x->getPosition();	//��ȡ���Ƿɻ�������
		if (rect.containsPoint(point))		//���л������Ƿɻ��ľ�����
		{
			Control::getInstance()->removeEnenyList(enemy);
			auto bomeff = bomEff::create();
			this->addChild(bomeff);
			bomeff->playBomEff(enemy->getPosition());
			enemy->EnemyDeath();
			this->setHeroPlaneHp();
			Hp_Label_num->setString(String::createWithFormat("%d", Hero_Plane_Hp)->getCString());
			if (this->getHeroPlaneHp() <= 0)
			{
				auto bomeff = bomEff::create();
				bomeff->playBomEff(point);
				this->addChild(bomeff);
				HeroDeath();	//�������Ǳ�ը����
			}
		}
	}
	//�л��ӵ�������
	for (int i = enemy_bullet_list.size()-1; i >= 0; --i)
	{
		auto enemy_bullet = enemy_bullet_list.at(i);
		auto rect = this->x->getBoundingBox();
		auto point = enemy_bullet->getPosition();
		if (rect.containsPoint(point))
		{
			auto bomeff = bomEff::create();
			this->addChild(bomeff);
			bomeff->playBomEff(enemy_bullet->getPosition());
			enemy_bullet->removeFromParentAndCleanup(true);
			Control::getInstance()->removeEnenyBulletList(enemy_bullet);
			this->setHeroPlaneHp();
			Hp_Label_num->setString(String::createWithFormat("%d", Hero_Plane_Hp)->getCString());
			if (this->getHeroPlaneHp() <= 0)
			{
				auto bomeff = bomEff::create();
				bomeff->playBomEff(point);
				this->addChild(bomeff);
				HeroDeath();	//�������Ǳ�ը����
			}
		}
	}
	
	if(time == CReadFile::getInstance()->getBossTime())
	{
		speed = 1;
		auto warningbg = Sprite::create("pic/wsparticle_redground.png");
		warningbg->setPosition(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height * 0.6f);
		warningbg->setScale(0.8f);
		this->addChild(warningbg);

		auto warning = Sprite::create("pic/wsparticle_warning.png");
		warning->setPosition(warningbg->getPositionX(),warningbg->getPositionY());
		warning->setScale(0.8f);
		this->addChild(warning);

		auto act1 = MoveBy::create(0.1f, Vec2(warningbg->getContentSize().width, 0));
		auto act2 = CallFuncN::create([=](Node * node)
		{
			removeChild(warningbg);

		});
		auto act3 = CallFuncN::create([=](Node * node)
		{
			removeChild(warning);

		});
		auto delay = DelayTime::create(2);
		auto action1 = Sequence::create(delay,act1,act2,nullptr);
		auto action2 = Sequence::create(delay,act1,act3,nullptr);
		warningbg->runAction(action1);
		warning->runAction(action2);

		addEnemyBoss(CReadFile::getInstance()->getBossHp());
		this->schedule(SEL_SCHEDULE(&MainScene::addBossBullet),0.5f);
	}
	//�л�BOSS�������ӵ�
	for (int i = enemy_boss_list.size()-1; i >= 0; --i)
	{
		auto enemy_boss = enemy_boss_list.at(i);
		auto rect = enemy_boss->getBoundingBox();
		for (int i = bullet_list.size()-1; i >= 0; --i)	//ʹ�õ�������ӵ�����
		{
			auto bullet = bullet_list.at(i);
			auto point = bullet->getPosition();
			if (rect.containsPoint(point))
			{
				Control::getInstance()->removeBulletList(bullet);	//�����������ӵ�
				bullet->removeFromParentAndCleanup(true);
				auto bomeff = bomEff::create();
				bomeff->playBomEff(point);
				this->addChild(bomeff);
				enemy_boss->set_hp(enemy_boss->get_hp()-1);	
				if (enemy_boss->get_hp() <= 0)
				{
					auto bomeff = bomEff::create();
					bomeff->playBomEff(enemy_boss->getPosition());
					this->addChild(bomeff);
					Control::getInstance()->removeEnenyBossList(enemy_boss);
					enemy_boss->EnemyBossDeath();
					this->unschedule(SEL_SCHEDULE(&MainScene::addBossBullet));
					time = 0;
					score += 100;
					label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
				}
			}
		}
	}
}

void MainScene::HeroDeath()
{
	UserDefault::getInstance()->setIntegerForKey("score",score);
	int score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	if (score > score_win)
	{
		UserDefault::getInstance()->setIntegerForKey("beast_score",score);
	}
	m_pAr->stopAllActions();		//ֹͣ���Ƿɻ������ж���
	m_pAr->setVisible(false);
	auto bomeff = bomEff::create();
	bomeff->playBomEff(m_pAr->getPosition());
	this->addChild(bomeff);
	HeroPlaneActionEnd();
}

void MainScene::HeroPlaneActionEnd()
{
	auto LostLayer = LayerColor::create(Color4B(10,10,10,0));	//���һ��͸����
	this->unschedule(SEL_SCHEDULE(&MainScene::bg1Move));	//ֹͣ��ͼ����
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet));	//ֹͣ����ӵ�
	this->unschedule(SEL_SCHEDULE(&MainScene::is_crash));	//ֹͣ��ײ���
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet2));//ֹͣ��ӵл��ӵ�
	this->unschedule(SEL_SCHEDULE(&MainScene::addEnemy));	//ֹͣ��ӵл�
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet1));//ֹͣ�����������ӵ�
	this->unschedule(SEL_SCHEDULE(&MainScene::addBossBullet));
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet3));
	for (int i = Control::getInstance()->getEnemyList().size()-1; i >= 0; --i)
	{
		auto enemy = Control::getInstance()->getEnemyList().at(i);
		enemy->unscheduleUpdate();		//ֹͣ�л��˶�
	}
	for (int i = Control::getInstance()->getBulletList().size()-1; i >=0; --i)
	{
		auto bullet = Control::getInstance()->getBulletList().at(i);
		bullet->unscheduleUpdate();		//ֹͣ�ӵ��˶�
	}
	for (int i = Control::getInstance()->getEnemyBulletList().size()-1; i >= 0; --i)
	{
		auto enemyBullet = Control::getInstance()->getEnemyBulletList().at(i);
		enemyBullet->unscheduleUpdate();//ֹͣ�л��ӵ��˶�
	}
	for (int i = Control::getInstance()->getEnemyBossList().size()-1; i >= 0; --i)
	{
		auto enemyBoss = Control::getInstance()->getEnemyBossList().at(i);
		enemyBoss->pauseSchedulerAndActions();
	}
	this->addChild(LostLayer);
	auto test = EventListenerTouchOneByOne::create();
	test->setSwallowTouches(true);
	test->onTouchBegan = [](Touch *pTouch, Event *pEvent)->bool{return true;};	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(test,LostLayer);
	////////////////////////////////////�������һ�ΰ�ť//////////////////////////////////////

	auto size = Director::getInstance()->getWinSize();		//��ȡ���ڴ�С
	auto againButton = MyButton::CreateButton();
	againButton->m_init("pic/again.png",[=](cocos2d::Ref* pSender){
		auto act1 = MoveBy::create(0.1f, Vec2(LostLayer->getContentSize().width, 0));
		auto act2 = CallFuncN::create([=](Node * node)
		{
			removeChild(LostLayer);

		});
		auto action = Sequence::create(act1,act2,nullptr);
		LostLayer->runAction(action);
		initHeroPlane();
		Hp_Label_num->setString(String::createWithFormat("%d", Hero_Plane_Hp)->getCString());
		
		this->schedule(SEL_SCHEDULE(&MainScene::bg1Move));				//��ͼ����
		this->schedule(SEL_SCHEDULE(&MainScene::is_crash));				//��ײ���
		this->schedule(SEL_SCHEDULE(&MainScene::addBossBullet),0.5f);
		this->schedule(SEL_SCHEDULE(&MainScene::addEnemy),CReadFile::getInstance()->getEnemyTime());		//��ӵл�
		this->schedule(SEL_SCHEDULE(&MainScene::addBullet2),1.5f);		//�л��ӵ�
		for (int i = Control::getInstance()->getEnemyList().size()-1; i >= 0; --i)
		{
			auto enemy = Control::getInstance()->getEnemyList().at(i);
			enemy->scheduleUpdate();	
		}
		for (int i = Control::getInstance()->getBulletList().size()-1; i >=0; --i)
		{
			auto bullet = Control::getInstance()->getBulletList().at(i);
			bullet->scheduleUpdate();		
		}
		for (int i = Control::getInstance()->getEnemyBulletList().size()-1; i >= 0; --i)
		{
			auto enemyBullet = Control::getInstance()->getEnemyBulletList().at(i);
			enemyBullet->scheduleUpdate();
		}
		for (int i = Control::getInstance()->getEnemyBossList().size()-1; i >= 0; --i)
		{
			auto enemyBoss = Control::getInstance()->getEnemyBossList().at(i);
			enemyBoss->resumeSchedulerAndActions();
		}
		if (score < 200)
		{
			this->schedule(SEL_SCHEDULE(&MainScene::addBullet),0.1f);		//����ӵ�
		}
		if (score >= 200)
		{
			this->unschedule(SEL_SCHEDULE(&MainScene::addBullet));
			this->schedule(SEL_SCHEDULE(&MainScene::addBullet1),0.1f);
		}
		if (score >= 500)
		{
			this->schedule(SEL_SCHEDULE(&MainScene::addBullet3),1.0f);
		}
	});
	againButton->setPosition(ccp(size.width/2,420));
	LostLayer->addChild(againButton);
	////////////////////////////////////////�������˵���ť//////////////////////////////////
	auto backmenu = MyButton::CreateButton();
	backmenu->m_init("pic/back.png",CC_CALLBACK_0(MainScene::BackMenuCallBack,this));
	backmenu->setPosition(ccp(size.width/2,320));
	LostLayer->addChild(backmenu);
}
	
void MainScene::AddPauseLayer()
{
	auto layer = LayerColor::create(Color4B(10,10,10,0));	//���һ��͸����
	auto test = EventListenerTouchOneByOne::create();
	test->setSwallowTouches(true);
	test->onTouchBegan = [](Touch *pTouch, Event *pEvent)->bool{return true;};	

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(test,layer);
	this->addChild(layer,2);
	m_pAr->pauseSchedulerAndActions();	//��ͣ���Ƿɻ������ж���	

	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet));	//ֹͣ����ӵ�
	this->unschedule(SEL_SCHEDULE(&MainScene::is_crash));	//ֹͣ��ײ���
	this->unschedule(SEL_SCHEDULE(&MainScene::bg1Move));	//ֹͣ��ͼ����
	this->unschedule(SEL_SCHEDULE(&MainScene::addEnemy));	//ֹͣ��ӵл�
	this->unschedule(SEL_SCHEDULE(&MainScene::is_crash));	//ֹͣ��ײ���
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet1)); //ֹͣ�����������ӵ�
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet2)); //ֹͣ��ӵл��ӵ�
	this->unschedule(SEL_SCHEDULE(&MainScene::addBullet3)); 
	for (int i = Control::getInstance()->getEnemyList().size()-1; i >= 0; --i)
	{
		auto enemy = Control::getInstance()->getEnemyList().at(i);
		enemy->unscheduleUpdate();		//ֹͣ�л��˶�
	}
	for (int i = Control::getInstance()->getBulletList().size()-1; i >=0; --i)
	{
		auto bullet = Control::getInstance()->getBulletList().at(i);
		bullet->unscheduleUpdate();		//ֹͣ�ӵ��˶�
	}
	for (int i = Control::getInstance()->getEnemyBulletList().size()-1; i >= 0; --i)
	{
		auto enemyBullet = Control::getInstance()->getEnemyBulletList().at(i);
		enemyBullet->unscheduleUpdate();//ֹͣ�л��ӵ��˶�
	}
	for (int i = Control::getInstance()->getEnemyBossList().size()-1; i >= 0; --i)
	{
		auto enemyBoss = Control::getInstance()->getEnemyBossList().at(i);
		enemyBoss->pause();
	}
	//////////////////////////////////////��Ӽ�����Ϸ��ť////////////////////////////////////
	auto size = Director::getInstance()->getWinSize();		//��ȡ���ڴ�С
	auto jixuButton = MyButton::CreateButton();
	jixuButton->m_init("pic/jixu.png",[=](cocos2d::Ref* pSender){
		auto act1 = MoveBy::create(0.1f, Vec2(layer->getContentSize().width, 0));
		auto act2 = CallFuncN::create([=](Node * node)
			{
				removeChild(layer);
			});
		auto action = Sequence::create(act1,act2,nullptr);
		layer->runAction(action);
		this->schedule(SEL_SCHEDULE(&MainScene::bg1Move));				//��ͼ����
		this->schedule(SEL_SCHEDULE(&MainScene::addEnemy),CReadFile::getInstance()->getEnemyTime());		//��ӵл�
		this->schedule(SEL_SCHEDULE(&MainScene::is_crash));				//��ײ���
		this->schedule(SEL_SCHEDULE(&MainScene::addBullet2),1.5f);		//��ӵл��ӵ�
		m_pAr->resumeSchedulerAndActions();		//�ָ����Ƿ��ж���
		for (int i = Control::getInstance()->getEnemyList().size()-1; i >= 0; --i)
		{
			auto enemy = Control::getInstance()->getEnemyList().at(i);
			enemy->scheduleUpdate();	
		}
		for (int i = Control::getInstance()->getBulletList().size()-1; i >=0; --i)
		{
			auto bullet = Control::getInstance()->getBulletList().at(i);
			bullet->scheduleUpdate();		
		}
		for (int i = Control::getInstance()->getEnemyBulletList().size()-1; i >= 0; --i)
		{
			auto enemyBullet = Control::getInstance()->getEnemyBulletList().at(i);
			enemyBullet->scheduleUpdate();
		}
		for (int i = Control::getInstance()->getEnemyBossList().size()-1; i >= 0; --i)
		{
			auto enemyBoss = Control::getInstance()->getEnemyBossList().at(i);
			enemyBoss->resume();
		}
		if (score < 200)
		{
			this->schedule(SEL_SCHEDULE(&MainScene::addBullet),0.1f);		//����ӵ�
		}
		if (score >= 200)
		{
			this->unschedule(SEL_SCHEDULE(&MainScene::addBullet));
			this->schedule(SEL_SCHEDULE(&MainScene::addBullet1),0.1f);
		}
		if (score >= 500)
		{
			this->schedule(SEL_SCHEDULE(&MainScene::addBullet3),1.0f);
		}
	});
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	jixuButton->setPosition(ccp(size.width/2, size.height/1.6f));
#else
	jixuButton->setPosition(ccp(size.width/2, size.height/1.6f));
	jixuButton->setScale(1.5f);
#endif
	layer->addChild(jixuButton);
	////////////////////////////////////////�������˵���ť//////////////////////////////////
	auto backmenu = MyButton::CreateButton();
	backmenu->m_init("pic/back.png",CC_CALLBACK_0(MainScene::BackMenuCallBack,this));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	backmenu->setPosition(ccp(size.width/2, size.height/3.8f));
#else
	backmenu->setPosition(ccp(size.width/2, size.height/3.8f));
	backmenu->setScale(1.5f);
#endif
	layer->addChild(backmenu);
}
	
void MainScene::BackMenuCallBack()
{
	auto scene = StartScene::createScene();
	Control::getInstance()->clear();
	Director::getInstance()->replaceScene(scene);
}

void MainScene::bomClear()
{
	auto size = Director::getInstance()->getWinSize();
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("pic/bom.ExportJson");
	auto m_pAr1 = Armature::create("bom");
	m_pAr1->getAnimation()->play("run");
	m_pAr1->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
	this->addChild(m_pAr1);
	if (UserDefault::getInstance()->getBoolForKey("Effect") == true)
	{
		Sound::getInstance()->playEffect("music/bom.wav");
	}
	auto & enemy_list = Control::getInstance()->getEnemyList();	//��ȡ�л�����
	auto & enemy_bullet_list = Control::getInstance()->getEnemyBulletList();//��ȡ�л��ӵ�����
	auto & enemy_boss_list = Control::getInstance()->getEnemyBossList();	//��ȡboss����
	for(int i = enemy_bullet_list.size()-1; i >= 0; --i)
	{
		auto enemy_bullet = enemy_bullet_list.at(i);
		enemy_bullet->removeFromParent();
	}
	enemy_bullet_list.clear();
	for(int i = enemy_list.size()-1; i >= 0; --i)
	{
		auto enemy = enemy_list.at(i);
		enemy_list.erase(i);
		enemy->EnemyDeath();
		score += 10;
		label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
	}
	for (int i = enemy_boss_list.size()-1; i >= 0; --i)
	{
		auto boss = enemy_boss_list.at(i);
		boss->set_hp(boss->get_hp()-100);
		if (boss->get_hp() <= 0)
		{
			Control::getInstance()->removeEnenyBossList(boss);
			boss->EnemyBossDeath();
			time = 0;
			score += 1000;
			label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
		}
	}
	auto delay  = DelayTime::create(1);
	auto m_delete = [=](){
		m_pAr1->removeFromParentAndCleanup(true);
	};
	m_pAr1->runAction(Sequence::create(delay,m_delete,RemoveSelf::create(),NULL));
}

void MainScene::addBossBullet(float dt)
{
	auto & boss_list = Control::getInstance()->getEnemyBossList();	//��ȡboss����
	for (int i = boss_list.size() - 1; i >= 0; --i)	//ʹ�õ������boss����
	{
		auto boss = boss_list.at(i);	
		{
			auto bullet = Bullet::create();
			bullet->initBullet(BULLET_4);
			auto point = ccp(boss->getPositionX()-boss->getContentSize().width*0.3f,boss->getPositionY()+boss->getContentSize().height/2);
			bullet->setPosition(point);
			bullet->setScale(0.5f);
			this->addChild(bullet);
			Control::getInstance()->setEnemyBulletList(bullet);
		}
		{
			auto bullet = Bullet::create();
			bullet->initBullet(BULLET_4);
			auto point = ccp(boss->getPositionX()+boss->getContentSize().width*0.3f,boss->getPositionY()+boss->getContentSize().height/2);
			bullet->setPosition(point);
			bullet->setScale(0.5f);
			this->addChild(bullet);
			Control::getInstance()->setEnemyBulletList(bullet);
		}
	}
}





