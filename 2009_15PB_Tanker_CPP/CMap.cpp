#include "CMap.h"

/*���˵���ʼ����ͼ*/
bool CMap::SetMap(int index)
{
	short x = 3, y = 5, y2 = 5, x2;
	if (index == 1) {			//�ؿ�1
#pragma region ע�����			//ע�����
		for (x2 = MAP_W / 3 - 3, y = 0; y < 2; y++)
			for (x = 0; x < 4; x++)
				map[y + y2][x + x2].Rever = true;
		for (x2 += 6, y = 0; y < 2; y++)
			for (x = 0; x < 4; x++)
				map[y + y2][x + x2].Rever = true;
		for (x2 += 6, y = 0; y < 2; y++)
			for (x = 0; x < 4; x++)
				map[y + y2][x + x2].Rever = true;
#pragma endregion
#pragma region ע����ǽ			//ע����ǽ
		y2 += 5; x2 = MAP_W / 3 - 3;
		for (y = 0; y < 2; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Wall = true;
		for (x2 += 6, y = 0; y < 2; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Wall = true;
		for (x2 += 6, y = 0; y < 2; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Wall = true;
#pragma endregion
#pragma region ע���ƺ			//ע���ƺ
		y2 += 4; x2 = MAP_W / 3 - 3;
		for (y = 0; y < 3; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Grass = true;
		for (x2 += 6, y = 0; y < 3; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Grass = true;
		for (x2 += 6, y = 0; y < 3; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Grass = true;
#pragma endregion
#pragma region ע����ǽ			//ע����ǽ
		y2 += 5; x2 = MAP_W / 3 - 3;
		for (y = 0; y < 3; y++)
			for (x = 0; x < 6; x++)
				map[y + y2][x + x2].Earth = true;
		for (x2 += 6, y = 0; y < 3; y++)
			for (x = 0; x < 6; x++)
				map[y + y2][x + x2].Earth = true;
		for (x2 += 6, y = 0; y < 3; y++)
			for (x = 0; x < 3; x++)
				map[y + y2][x + x2].Earth = true;
#pragma endregion
		return true;
	}
	else if (index == 2) {		//�ؿ�2
#pragma region ע����ǽ1		//ע����ǽ1
		for (x2 = 0, y = 0; y < 3; y++)
			for (x = 0; x < MAP_W; x++)
				map[y + y2][x + x2].Earth = true;
#pragma endregion
#pragma region ע����ǽ			//ע����ǽ
		y2 += 5; x2 = MAP_W / 3 - 4;
		for (y = 0; y < 2; y++)
			for (x = 0; x < 6; x++)
				map[y + y2][x + x2].Rever = true;
		for (x2 += 6, y = 0; y < 2; y++)
			for (x = 0; x < 6; x++)
				map[y + y2][x + x2].Rever = true;
		for (x2 += 6, y = 0; y < 2; y++)
			for (x = 0; x < 6; x++)
				map[y + y2][x + x2].Rever = true;
#pragma endregion
#pragma region ע���ƺ			//ע���ƺ
		y2 += 4; x2 = 0;
		for (y = 0; y < 3; y++)
			for (x = 0; x < MAP_W; x++)
				map[y + y2][x + x2].Grass = true;
#pragma endregion
#pragma region ע����ǽ2		//ע����ǽ2
		y2 += 5; x2 = 0;
		for (y = 0; y < 3; y++)
			for (x = 0; x < MAP_W; x++)
				map[y + y2][x + x2].Earth = true;
#pragma endregion
		return true;
	}
	else {
		gGINFO.levels = 1;
	}
	return false;
}

/*��������Ϣ�ı��ͼ*/
bool CMap::SetMap(COORD xy, CHARMAP stmap, bool isTank)
{
	short i, j;
	if (isTank) {
		for (i = -1; i < 2; i++)
		{
			for (j = -1; j < 2; j++)
			{
				map[xy.Y + j][xy.X + i].TANKER = stmap.TANKER;
			}
		}
	}
	else {
		map[xy.Y][xy.X] = stmap;
	}
	return true;
}

