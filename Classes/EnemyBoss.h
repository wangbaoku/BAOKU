#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class EnemyBoss:public Sprite
{
public:
	EnemyBoss(void);
	~EnemyBoss(void);

	virtual bool init();
	void initEnemyBoss(int index = 1);
	virtual void update(float delta);
	void EnemyBossDeath();
	void RemoveEnemyBoss();
	void onEnterTransitionDidFinish();
	void onExit();
	void set_hp(int hp);
	int get_hp(){ return enemybosshp; }
	CREATE_FUNC(EnemyBoss);
	bool is_death;
private:
	int enemybosshp;
};

