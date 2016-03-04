#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class StartScene:public Layer		//继承Layer 
{
public:
	StartScene(void);
	~StartScene(void);
	bool init();					//初始化
	static Scene* createScene();	//创建场景
	CREATE_FUNC(StartScene);		//手动实现创建方法
	void StartButtonCallBack();		//开始按钮回调
	void OptionButtonCallBack();		//设置按钮回调
	void QuitButtonCallBack();		//退出按钮回调


};

#endif // !__STARTSCENE__
