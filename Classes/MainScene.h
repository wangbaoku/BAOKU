#pragma once
#ifndef _MAIN_SCENE_H__
#define _MAIN_SCENE_H__
#include "cocos2d.h"
#include "Control.h"
#include "cocostudio\CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

class MainScene:public Layer
{
public:
	MainScene(void);
	~MainScene(void);
	static Scene* createScene();
	bool init();
	CREATE_FUNC(MainScene);
	void bg1Move(float delta);
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onEnterTransitionDidFinish();
	void onExit();
	void initHeroPlane();		//��ʼ�����Ƿɻ�
	void addEnemy(float dt);			//��ӵл�
	void addBullet(float);				//����ӵ�
	void is_crash(float tm);			//��ײ���
	void HeroDeath();					//���Ƿɻ���ըЧ��
	void HeroPlaneActionEnd();			//���Ƿɻ���ը��
	void AddPauseLayer();				//�����ͣ��
	void BackMenuCallBack();			//���ذ�ť�ص�
	void addBullet1(float dt);			//�����ӵ�
	void addBullet2(float dt);
	void addBullet3(float dt);
	void addEnemyBoss(int enemyBossHp);
	void setHeroPlaneHp();
	int getHeroPlaneHp(){return Hero_Plane_Hp;}
	void bomClear();
	void addBossBullet(float dt);
private:
	Sprite * bg1;		//��һ�ű�����ͼ
	Sprite * bg2;		//�ڶ��ű�����ͼ
	Sprite * Hero_Plane;	//���Ƿɻ�
	int Hero_Plane_Hp;
	int score; //��ǰ����
	Label* label_score_num_; //��ǰ��
	Label* label_best_score_num_; // ��߷�
	Bullet * bullet;
	Label* Hp_Label_num;
	int index;
	int time;
	Armature * m_pAr;
	Sprite * x;
	int speed;
};
#endif // !_MAIN_SCENE_H__

