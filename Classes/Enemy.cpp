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
	//�л�Ѫ��
	enemy_hp_ = index;
	//��ʼ���л�
	string name_str = String::createWithFormat("pic/Enemy_%d.png", index)->getCString();
	//��ӵл�ͼƬ
	this->initWithFile(name_str);

	//��ȡ��Ļ��С
	Size size = Director::getInstance()->getWinSize();
	//����л�����
	Point pos = ccp(CCRANDOM_0_1()*(size.width - this->getContentSize().width) + this->getContentSize().width / 2, size.height);
	this->setPosition(pos);

}

void Enemy::EnemyDeath()
{
	is_death_ = true;
	//��ը
	RemoveEnemy();
}

void Enemy::update( float delta )
{
	//�����ը���ƶ�
	if (is_death_)
		return;
	//ʵ�ֵл��˶�
	auto point = this->getPositionY() - 2;
	this->setPositionY(point);
	//����ƶ�������Ļ��Ӹ��ڵ����Ƴ�
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