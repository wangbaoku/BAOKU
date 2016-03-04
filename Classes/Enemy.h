#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Enemy:public Sprite
{
public:
	Enemy(void);
	~Enemy(void);
	virtual bool init();
	CREATE_FUNC(Enemy);
	virtual void update(float delta);
	void initEnemy(int index = 1);
	void EnemyDeath();
	void RemoveEnemy();
	void onEnterTransitionDidFinish();
	void onExit();
	//µÐ»úÑªÁ¿
	void set_hp(int hp);
	int get_hp(){ return enemy_hp_; }
private:
	int enemyIndex;
	bool is_death_;
	int enemy_hp_;
};

