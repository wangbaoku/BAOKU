#include "bomEff.h"


bomEff::bomEff(void)
{
	playEnd = false;
}


bomEff::~bomEff(void)
{
}

bool bomEff::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

bool bomEff::playBomEff( Vec2 pos )
{
	auto animation = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		auto  bomeff = String::createWithFormat("pic/b%d.png", i);
		animation->addSpriteFrameWithFile(bomeff->getCString());
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	//auto a = Animate::create(animation);
	this->runAction(Sequence::create(Animate::create(animation),CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	}), NULL));
	this->setPosition(pos);
	return true;
}

