#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBoss.h"
class Control
{
public:
	Control(void);
	~Control(void);
	static Control* getInstance();
	Vector<Enemy*> &getEnemyList(){return enemyList;}
	Vector<Bullet*> &getBulletList(){return bulletList;}
	Vector<Bullet*> &getEnemyBulletList(){return enemyBulletList;}
	Vector<EnemyBoss*> &getEnemyBossList(){return enemyBossList;}
	void setEnemyList(Enemy * enemy);
	void setBulletList(Bullet * bullet);
	void setEnemyBulletList(Bullet * bullet);
	void setEnemyBossList(EnemyBoss * enemyBoss);
	void removeEnenyList(Enemy * enemy);
	void removeBulletList(Bullet * bullet);
	void removeEnenyBulletList(Bullet * bullet);
	void removeEnenyBossList(EnemyBoss * enemyBoss);
	bool isEnemyNull();
	void clear();
private:
	Vector<Enemy*> enemyList;
	Vector<Bullet*> bulletList;
	Vector<Bullet*> enemyBulletList;
	Vector<EnemyBoss*> enemyBossList;
};

