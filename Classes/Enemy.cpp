#include "Enemy.h"
#include "Control.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

bool Enemy::init()
{
	
	is_death_ = false;
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Enemy::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void Enemy::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void Enemy::initEnemy( int index /*= 1*/ )
{
	//敌机血量
	enemy_hp_ = index;
	//初始化敌机
	string name_str = String::createWithFormat("pic/Enemy_%d.png", index)->getCString();
	//添加敌机图片
	this->initWithFile(name_str);

	//获取屏幕大小
	Size size = Director::getInstance()->getWinSize();
	//随机敌机坐标
	Point pos = ccp(CCRANDOM_0_1()*(size.width - this->getContentSize().width) + this->getContentSize().width / 2, size.height);
	this->setPosition(pos);

}

void Enemy::EnemyDeath()
{
	is_death_ = true;
	//爆炸
	RemoveEnemy();
}

void Enemy::update( float delta )
{
	//如果爆炸不移动
	if (is_death_)
		return;
	//实现敌机运动
	auto point = this->getPositionY() - 2;
	this->setPositionY(point);
	//如果移动出了屏幕则从父节点中移除
	if (point < -this->getContentSize().height)
	{
		this->removeFromParentAndCleanup(true);
		Control::getInstance()->removeEnenyList(this);
	}
}

void Enemy::RemoveEnemy()
{
	Control::getInstance()->removeEnenyList(this);
	this->removeFromParentAndCleanup(true);
}

void Enemy::set_hp(int hp)
{
	enemy_hp_ = hp;
}