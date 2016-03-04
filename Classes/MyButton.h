#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MyButton:public Sprite
{

public:
	MyButton(void);
	~MyButton(void);
	bool init();
	void m_init(string name,const ccMenuCallback _CallBack);		
	static MyButton* CreateButton();
	CREATE_FUNC(MyButton);

private:
	string m_Name;
	ccMenuCallback	 m_callback;
	Sprite* m_image;
};

