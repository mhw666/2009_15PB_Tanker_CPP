#pragma once
#include <list>
using std::list;
#include "CView.h"
#include "CMap.h"
#include "CBgm.h"

class CCtrl
{
public:
	CCtrl(COORD xy);
	~CCtrl();

	bool InitCMD();
	int Go(int GameMode = 1, int Checkpoint = 1);
	void GoKey(byte& key, unsigned int msecond);
	CTanker cT[7];
private:
	void SetTank(int TankI);
	bool AddBullet(byte tid);
	bool MoveBullet(CBullet& att, bool clean = false);
	bool MoveTank(unsigned int& mSecond);
	bool CheckTank(COORD& xy, byte tid);
	void PrintGInfo(unsigned int& msecond, WORD color = 0x0E);
	bool FindBullet(COORD xy, byte* tid);
	bool DrawMap();
private:
	CView*	PV;
	CMap*	PM;
	CBgm	PB;
	COORD	_maxXY;
	byte	_tanks = 0x04;
	list<CBullet> _bullets;
};
