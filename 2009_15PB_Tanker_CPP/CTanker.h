#pragma once
#include "CData.h"

class CTanker
{
friend class CView;
friend class CAStar;
public:
	CTanker();
	~CTanker();

	void Init(COORD xy, int blood, int tid = 0, byte dir = 'W',
		byte team = 'A', WORD color = 0x0F, int speed = 200,
		int power = 20) {
		this->_oxy.X = xy.X; this->_oxy.Y = xy.Y;
		this->_tid = tid;	 this->_dir = dir;
		this->_color = color;this->_blood = blood;
		this->_team = team;
		this->_speed = speed;this->_power = power;
		this->mSecond = 0;	this->_kills = 0;
	};
	

	byte GetDir(bool to0123 = true) {
		if (to0123) {
			switch (this->_dir) {
			case 'W': return 0x00;
			case 'A': return 0x01;
			case 'D': return 0x02;
			case 'S': return 0x03; }
		}
		return this->_dir;
	};
	byte GetTid() { return _tid; };
	bool TryMove(byte dir = NULL);
	bool CheckMap();

	COORD GetOldXY() { return _oxy; };
	/*移动坦克函数*/
	COORD Move();

	int GetInfo2() { return this->_kills * 10; };
	void GetInfo(int* infos) {
		infos[0] = this->_blood;
		if (_blood > 999) infos[0] = 999;
		infos[1] = this->_speed;
		infos[2] = this->_power;
		infos[3] = this->_kills;
		infos[4] = this->_kills * 10;
	};
	bool IsAlive() { return this->_blood > 0; };
	int GetPower() { return _power; };
	int GetBlood() { return _blood; };
	int GetSpeed() { return _speed; };
	void SetBlood(int blood) { _blood = blood; };
	void SetSpeed(int speed) { _speed = speed; };
	void AddKills() { ++_kills; };
	byte GetTeam() { return _team; };


public:		//	//	//对外变量
	unsigned int mSecond = 0;	//定义毫秒数

protected:	//	//	//保护变量
	COORD _oxy = { 0,0 };
	COORD _nxy = { 0,0 };
	byte _tid = 0;
	byte _dir = 'W';
	byte _team = 'A';
	WORD _color = 0x0F;
	int _blood = 0;

private:	//	//	//对内变量
	int _speed = 300;
	int _power = 35;
	int _kills = 0;
};