#include "CView.h"

/*初始化窗口*/
bool CView::InitWindow(COORD& xy, bool isCursor)
{
	CONSOLE_CURSOR_INFO cursor = { 1,isCursor };
	char buf[50] = {0};
	SetConsoleCursorInfo(gOUTPUT, &cursor);
	sprintf_s(buf, "mode con cols=%d lines=%d", xy.X, xy.Y);
	system(buf);
	system("Color 0F");
	//函数改变大小
	//SMALL_RECT srctWindow = { 0,0,xy.X,xy.Y };
	//if (!SetConsoleWindowInfo(gOUTPUT, true, &srctWindow))
	//{	//设置控制台窗口大小
	//	printf_s("size err %d\n", GetLastError());
	//	return false;
	//}
	return (bool)SetConsoleTitleA(INFOMenu[0]);
}

/*绘制窗口函数*/
void CView::PrintPoint(COORD xy, const char* text, WORD color)
{
	if (color != 0x00)							//如果传入颜色
		SetConsoleTextAttribute(gOUTPUT, color);//则改变画刷
	xy.X = xy.X * 2 + 2; xy.Y++;				//转换窗口坐标
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	cout << text << flush;						//输出文字
	if (color != 0x00)
		SetConsoleTextAttribute(gOUTPUT, 0x0F);	//还原画刷
}

/*刷新窗口、绘画地图*/
void CView::PrintMap()
{
	unsigned short x = MAP_W + 1, y = 0;
	const char* sWall = MAPEnum[demap铁墙];
	gGINFO.start = GetTickCount64();	//存储当前时间
	system("cls");
	while (x--)
		cout << sWall;
	for (y = 0; y < MAP_H; ++y)
	{
		printf_s("%s\n%s", sWall, sWall);
		for (x = 0; x<MAP_W; ++x)
		{
			PrintMap(map[y][x]);
		}
	}
	cout << sWall << '\n'; x += 2;
	while (x--)
		cout << sWall;
	cout << endl;
}

/*重载绘画地图点*/
void CView::PrintMap(CHARMAP tmap)
{
	unsigned char index = 0x00;		//初始化打印索引
	if (tmap.Rever == true) {		//河流
		index = demap河流;
	}else if (tmap.Wall == true) {	//铁墙
		index = demap铁墙;
	}else if (tmap.Grass == true) {	//草地
		index = demap草坪;
	}else if (tmap.Earth == true) {	//土墙
		index = demap土墙;
	}
	SetConsoleTextAttribute(gOUTPUT, MColor[index]);
	cout << MAPEnum[index];			//通过索引打印相应颜色字符
	SetConsoleTextAttribute(gOUTPUT, 0x0F);
}

/*重载绘画坦克*/
void CView::PrintMap(CTanker& that, bool clean)
{
	if (!that.IsAlive()) return;
	SHORT i, dir = that.GetDir(), j;
	for (i = 0; !clean && i < 3; i++)
	{
		this->PrintPoint({ that._oxy.X - 1,that._oxy.Y + i - 1 },
			szTankSharp[that._team - 'A'][dir][i],
			that._color);
	}
	for (j = -1; j < 2; j++)		//草坪始终画草
		for (i = -1; i < 2; i++)	//循环坦克身体
		{
			if (map[that._oxy.Y + j][that._oxy.X + i].Grass == true)
				this->PrintPoint(	//如果是草坪，则画草
					{ that._oxy.X + i,that._oxy.Y + j },
					deStr草坪, deCol草坪);
			else if (clean) {		//否则画刷空白
				this->PrintPoint(	//画空
					{ that._oxy.X + i,that._oxy.Y + j },
					deStr空地);
			}
		}
}

/*重载绘制游戏信息*/
void CView::PrintMap(byte menuIndex, bool err)
{
	if (menuIndex == gGINFO.menu && !err)
		return;
	else gGINFO.menu = menuIndex;
	if (gGINFO.count++ > 7) PB.PlayOp();
	if (gGINFO.count > 9) gGINFO.count = 0xF7;
	byte x = MAP_W / 2 - 4, y = MAP_H / 2 - 4,
		i, max = 6;
	for (i = 1; i < max; i++)
	{
		this->PrintPoint({ x,y + i }, INFOMenu[i],
			i == menuIndex ? deCol草坪 : 0x0F);
	}
	x -= 4; ++y;
	this->PrintPoint({ x,y + i }, VIEWINFO[err ? 1 : 0],
		err ? 0x04 : 0x0F);
}

/*保存游戏*/
bool CView::SaveGame(CTanker* Tanks)
{
	FILE* pFile = nullptr;						//定义文件指针变量
	fopen_s(&pFile, ".//Data//TankData.bin", "wb+");	//获取文件指针
	if (pFile == nullptr) return false;			//判断打开文件失败
	fwrite(Tanks, sizeof(CTanker), 7, pFile);	//写入坦克数组内容
	fclose(pFile);	pFile = nullptr;			//关闭文件指针

	fopen_s(&pFile, ".//Data//Map.bin", "wb+");	//获取文件指针
	if (pFile == nullptr) return false;			//判断打开文件失败
	fwrite(map, MAP_W * MAP_H, 1, pFile);		//写入地图数组内容
	fclose(pFile);	pFile = nullptr;			//关闭文件指针

	fopen_s(&pFile, ".//Data//GInfo.bin", "wb+");//获取文件指针
	if (pFile == nullptr) return false;			//判断打开文件失败
	fwrite(&gGINFO, sizeof(gGINFO), 1, pFile);	//写入游戏信息内容
	fclose(pFile);	pFile = nullptr;			//关闭文件指针
	return true;
}

/*读取游戏*/
bool CView::ReadGame(CTanker* Tanks)
{
	FILE* pFile = nullptr;						//定义文件指针变量
	fopen_s(&pFile, ".//Data//TankData.bin", "r");	//获取文件指针
	if (pFile == nullptr) return false;			//如果失败，则返回
	fread(Tanks, sizeof(CTanker), 7, pFile);	//读取坦克数组内容
	fclose(pFile);	pFile = nullptr;			//关闭文件指针

	fopen_s(&pFile, ".//Data//Map.bin", "r");	//获取文件指针
	if (pFile == nullptr) return false;			//如果失败，则返回
	fread(map, MAP_W * MAP_H, 1, pFile);		//读取地图数组内容
	fclose(pFile);	pFile = nullptr;			//关闭文件指针

	for (byte x = 0; x < MAP_W; x++)			//循环地图
		for (byte y = 0; y < MAP_H; y++)		//循环地图
			map[y][x].Bullet = false;			//将子弹清除

	fopen_s(&pFile, ".//Data//GInfo.bin", "r");	//获取文件指针
	if (pFile == nullptr) return false;			//如果失败，则返回
	fread(&gGINFO, sizeof(gGINFO), 1, pFile);	//读取游戏信息内容
	fclose(pFile);	pFile = nullptr;			//关闭文件指针
	return true;
}
