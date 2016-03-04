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
	void initHeroPlane();		//初始化主角飞机
	void addEnemy(float dt);			//添加敌机
	void addBullet(float);				//添加子弹
	void is_crash(float tm);			//碰撞检测
	void HeroDeath();					//主角飞机爆炸效果
	void HeroPlaneActionEnd();			//主角飞机爆炸后
	void AddPauseLayer();				//添加暂停层
	void BackMenuCallBack();			//返回按钮回调
	void addBullet1(float dt);			//升级子弹
	void addBullet2(float dt);
	void addBullet3(float dt);
	void addEnemyBoss(int enemyBossHp);
	void setHeroPlaneHp();
	int getHeroPlaneHp(){return Hero_Plane_Hp;}
	void bomClear();
	void addBossBullet(float dt);
private:
	Sprite * bg1;		//第一张背景地图
	Sprite * bg2;		//第二张背景地图
	Sprite * Hero_Plane;	//主角飞机
	int Hero_Plane_Hp;
	int score; //当前分数
	Label* label_score_num_; //当前分
	Label* label_best_score_num_; // 最高分
	Bullet * bullet;
	Label* Hp_Label_num;
	int index;
	int time;
	Armature * m_pAr;
	Sprite * x;
	int speed;
};
#endif // !_MAIN_SCENE_H__

