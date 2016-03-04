#include "Bullet.h"
#include "Control.h"
#include "math/CCMath.h"

Bullet::Bullet(void)
	:m_enemyNode(0)
{
	m_bOnce = false;
}

Bullet::~Bullet(void)
{
}

bool Bullet::init()
{
	time = 0;
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Bullet::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void Bullet::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void Bullet::initBullet(BULLET_TYPE type)
{
	m_type = type;
	if (type == BULLET_1)
	{
		if (UserDefault::getInstance()->getIntegerForKey("index") == 0)
		{
			bullet = Sprite::create("pic/Heroplane1bullet.png");
		}
		else
		{
			bullet = Sprite::create("pic/Heroplane2bullet.png");
		}	
		this->addChild(bullet);
	}
	if (type == BULLET_2)
	{
		bullet = Sprite::create("pic/Bullet2.png");		
		this->addChild(bullet);
	}
	if (type == BULLET_3)
	{
		bullet = Sprite::create("pic/Bullet3.png");		
		this->addChild(bullet);
	}
	if (type == BULLET_4)
	{
		bullet = Sprite::create("pic/Bullet2.png");
		this->addChild(bullet);
	}
}

void Bullet::update( float delta )
{
	if (m_type == BULLET_1)
	{
		this->setPositionY(this->getPositionY()+10);		
		if (this->getPositionY() > Director::getInstance()->getWinSize().height)
		{
			this->removeFromParentAndCleanup(true);
			Control::getInstance()->removeBulletList(this);

		}
	}
	if (m_type == BULLET_2)
	{
		time++;
		auto x = this->getParent()->getChildByName("Hero_Plane")->getChildByName("x");
		float destX = x->getPositionX() - getPositionX();
		float destY = x->getPositionY() - getPositionY();

		if (time < 20)
		{
			float anglef = atan2f(destY, destX);
			setRotation(anglef / 3.14159 * 90);
			a = cosf(anglef) * 5;
			b = sinf(anglef)* 5;
		}
		setPosition(getPositionX() + a, getPositionY() + b);
		if (this->getPositionY() < -Director::getInstance()->getWinSize().height/2)
		{
			this->removeFromParentAndCleanup(true);
			Control::getInstance()->removeBulletList(this);
		}
	}
	if (m_type == BULLET_3)
	{
		if (Control::getInstance()->isEnemyNull() == false)
		{
			m_enemyNode = Control::getInstance()->getEnemyList().at(0);
			auto ite = Control::getInstance()->getEnemyList().begin();
			while (ite != Control::getInstance()->getEnemyList().end())
			{
				if ((*ite)->getPositionY() > Director::getInstance()->getVisibleSize().height / 2.0f)
				{
					m_enemyNode = *ite;
					break;
				}
				ite++;
			}
		}
		else
		{
			m_enemyNode = 0;
		}

		float destX = getPositionX();
		float destY = getPositionY()+1;
		float anglef2 = 90;
		if (m_enemyNode)
		{
			destX = m_enemyNode->getPositionX() - getPositionX();
			destY = m_enemyNode->getPositionY() - getPositionY();
			anglef = atan2f(destY, destX);
			anglef2 = atan2f(destY, -destX);
			setRotation(anglef2 / 3.14159 * 180 - 90);
			m_bOnce = true;
		}
		else
		{
			if( !m_bOnce )
			{
				anglef = CC_DEGREES_TO_RADIANS( 90 );
			}
		}
		setPosition(getPositionX() + cosf(anglef) * 5, getPositionY() + sinf(anglef)* 5);
		Rect winRc( 0, 0, Director::getInstance()->getWinSize().width,Director::getInstance()->getWinSize().height );
		if (!winRc.containsPoint(this->getPosition()))
		{
			Control::getInstance()->removeBulletList(this);
			this->removeFromParentAndCleanup(true);
		}
	}
	if (m_type == BULLET_4)
	{
		this->setPositionY(this->getPositionY()-5);		
		if (this->getPositionY() < -200)
		{
			this->removeFromParentAndCleanup(true);
			Control::getInstance()->removeBulletList(this);

		}
	}
}


