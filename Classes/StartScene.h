#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class StartScene:public Layer		//�̳�Layer 
{
public:
	StartScene(void);
	~StartScene(void);
	bool init();					//��ʼ��
	static Scene* createScene();	//��������
	CREATE_FUNC(StartScene);		//�ֶ�ʵ�ִ�������
	void StartButtonCallBack();		//��ʼ��ť�ص�
	void OptionButtonCallBack();		//���ð�ť�ص�
	void QuitButtonCallBack();		//�˳���ť�ص�


};

#endif // !__STARTSCENE__
