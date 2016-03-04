#include "EnemyBoss.h"
#include "Control.h"

EnemyBoss::EnemyBoss(void)
{
}


EnemyBoss::~EnemyBoss(void)
{
}

bool EnemyBoss::init()
{
	is_death = false;
	enemybosshp = 0;
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void EnemyBoss::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void EnemyBoss::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void EnemyBoss::initEnemyBoss(int index)
{
	//初始化敌机
	string name_str = String::createWithFormat("pic/Enemy_Boss%d.png", index)->getCString();
	//添加敌机图片
	this->initWithFile(name_str);

	//获取屏幕大小
	Size size = Director::getInstance()->getWinSize();
	//敌机坐标
	Point pos = ccp(size.width/2, size.height * 0.8);
	
	auto moveAction = MoveTo::create(3.0f,Vec2(size.width-this->getContentSize().width/2,size.height * 0.8));	
	auto moveBackAction = MoveTo::create(3.0f,Vec2(this->getContentSize().width/2,size.height * 0.8));
	//auto movedown = MoveTo::create(3.0f,Vec2(size.width/2,size.height * 0.8));
	auto delayAction = DelayTime::create(3);
	this->runAction(delayAction);
	this->runAction(RepeatForever::create(Sequence::create(moveAction,moveBackAction,NULL)));
	this->setPosition(pos);
	this->set_hp(enemybosshp);
}

void EnemyBoss::EnemyBossDeath()
{
	this->stopAllActions();
	//爆炸
	auto animation = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		auto  enemy_name = String::createWithFormat("pic/b%d.png", i);
		animation->addSpriteFrameWithFile(enemy_name->getCString());
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(),
		CallFunc::create(CC_CALLBACK_0(EnemyBoss::RemoveEnemyBoss, this)), NULL));
	is_death = true;
}

void EnemyBoss::RemoveEnemyBoss()
{
	this->removeFromParentAndCleanup(true);

}

void EnemyBoss::set_hp( int hp )
{
	enemybosshp = hp;
}

void EnemyBoss::update( float delta )
{

}
