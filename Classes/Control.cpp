#include "Control.h"

static Control* _Instance = nullptr;

Control::Control(void)
{
}

Control::~Control(void)
{
}

Control* Control::getInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new Control;
	}
	return _Instance;
}

void Control::setEnemyList( Enemy * enemy )
{
	enemyList.pushBack(enemy);		//���л���ӵ��л������С�
}

void Control::setBulletList( Bullet * bullet )
{
	bulletList.pushBack(bullet);	//���ӵ���ӵ��ӵ�������
}

void Control::setEnemyBulletList(Bullet * bullet)
{
	enemyBulletList.pushBack(bullet);
}

void Control::removeEnenyList( Enemy * enemy )
{
	enemyList.eraseObject(enemy);	//���л��Ӷ�����ɾ��
}

void Control::removeBulletList( Bullet * bullet )
{
	bulletList.eraseObject(bullet);	//���ӵ��Ӷ�����ɾ��
}

bool Control::isEnemyNull()
{
	if (enemyList.size() == 0)
	{
		return true;
	}

	return false;
}

void Control::removeEnenyBulletList( Bullet * bullet )
{
	enemyBulletList.eraseObject(bullet);
}

void Control::setEnemyBossList( EnemyBoss * enemyBoss )
{
	enemyBossList.pushBack(enemyBoss);
}

void Control::removeEnenyBossList( EnemyBoss * enemyBoss )
{
	enemyBossList.eraseObject(enemyBoss);
}

void Control::clear()
{
	enemyList.clear();
	bulletList.clear();
	enemyBulletList.clear();
	enemyBossList.clear();
}
