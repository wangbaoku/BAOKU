#pragma once
#include "cocos2d.h"
#include "ui/UICheckBox.h"
#include "MyButton.h"

#include "cocostudio\CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class OptionScene:public Layer
{
public:
	OptionScene(void);
	~OptionScene(void);
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OptionScene);
	void backButtonCallback(cocos2d::Ref* pSender);
	void setIndex(int index);
	bool onTouchBegan(Touch *touch, Event *unused_event);
private:
	Sprite * kuang1;
	Sprite * kuang2;
	MyButton* m_box;
	int index;
	Sprite * Hero_Plane1;
	Sprite * Hero_Plane2;
	Sprite * plane_selected;
	Sprite * sound_selected;
	Sprite * effect_selected;
	Armature * m_pAr1;
	Armature * m_pAr2;
	bool m_Effect;
};

