#pragma once
#include <string>
#include <vector>
using namespace std;

class CReadFile
{
public:
	bool loadSpec();
	void saveUserInfo();
	string _getFileByName(string pFileName);
	bool _saveFile(const char *pContent, string pFileName);
	bool _isFileExist(string pFileName);
	void init();
	static CReadFile * getInstance();
	void setBossTime(int time){m_boss_time = time;}
	int getBossTime(){return m_boss_time;}
	void setEnemyTime(double time){m_enemy_time = time;}
	float getEnemyTime(){return m_enemy_time;}
	void setBossHp(int hp){m_boss_hp = hp;}
	int getBossHp(){return m_boss_hp;}
private:
	CReadFile(void);
	~CReadFile(void);
	int m_boss_time;
	double m_enemy_time;
	int m_boss_hp;
};