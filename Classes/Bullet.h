#ifndef _BULLET_H__
#define _BULLET_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

enum BULLET_TYPE
{
	BULLET_1,
	BULLET_2,
	BULLET_3,
	BULLET_4,
};
class Bullet:public Sprite
{
public:
	Bullet(void);
	~Bullet(void);
	virtual bool init();
	CREATE_FUNC(Bullet);
	void onEnterTransitionDidFinish();
	void onExit();
	void update(float delta);
	void initBullet(BULLET_TYPE type);
	Sprite * getSprite(){ return bullet; };
private:
	Sprite * bullet;
	BULLET_TYPE m_type;
	Node* m_enemyNode;
	Node* m_enemyBulletNode;
	int time;
	float a,b;
	float offsetX, offsetY;
	bool m_bOnce;
	float anglef;
};

#endif // !_BULLET_H__

