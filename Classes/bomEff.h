#pragma once
#include "cocos2d.h"
USING_NS_CC;
class bomEff:public Sprite
{
public:
	bomEff(void);
	~bomEff(void);
	virtual bool init();
	CREATE_FUNC(bomEff);
	bool playBomEff(Vec2 pos);
private:
	bool playEnd;
};

