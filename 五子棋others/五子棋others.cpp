// 五子棋others.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#define KEY_DOWN(vk_c)(GetAsyncKeyState(vk_c)&0x8000)	//键盘上的回车响应
typedef struct position {
	int x;				//棋盘的x坐标
	int y;				//棋盘的y坐标
}postype;
postype cur;			//棋子的中点坐标各减15
int sum=1;				//总共走过的步数
//COLORREF colorarr[2] = { RGB(249,214,91),RGB(255,0,0)};
//postype ballsarr[255];	//各个下棋点的坐标
COLORREF c1;				//表示c1的连珠数的颜色
int index = 5;
int chess[15][15] = { 0 };		//表示每个点的内容，无内容为0，黑子为1，白子为2
void showmap(void)		//画出棋盘
{
	initgraph(510, 510);
	setbkcolor(RGB(249,214,91));
	cleardevice();		//进行清屏处理使背景色显现
	setlinecolor(BLACK);	//线条颜色为黑
	for (int i = 1; i < 16; i++)	//横线
	{	
		line(30 , 30 * i, 15 * 30, 30 * i);
	}
	for ( i = 1; i < 16; i++)	//竖线
	{
		line(30*i , 30,  30 * i , 15 * 30);
	}
}
void wipe(postype)				//擦掉并重新生成光标
{
	setcolor(RGB(249, 214, 91));
	line(cur.x, cur.y, cur.x + 10, cur.y);
	line(cur.x, cur.y, cur.x, cur.y + 10);
	line(cur.x + 30, cur.y + 30, cur.x + 20, cur.y + 30);
	line(cur.x + 30, cur.y + 30, cur.x + 30, cur.y + 20);
}
void repaint(postype)
{
	setcolor(RED);
	line(cur.x, cur.y, cur.x + 10, cur.y);
	line(cur.x, cur.y, cur.x, cur.y + 10);
	line(cur.x + 30, cur.y + 30, cur.x + 20, cur.y + 30);
	line(cur.x + 30, cur.y + 30, cur.x + 30, cur.y + 20);
}
//换算法，判定下的位置的各方向的棋子是否构成五子
void judge()
{
	int i, j;
	for (i = 0; i < 10; i++)		//竖向检索
	{
		for (j = 0; j < 10; j++)
		{
			if (chess[i][j] == 1 && chess[i][j + 1] == 1 && chess[i][j + 2] == 1 && chess[i][j + 3] == 1 && chess[i][j + 4] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,黑方获胜");
				outtextxy(100, 100, str);
			}
			else if (chess[i][j] == 2 && chess[i][j + 1] == 2 && chess[i][j + 2] == 2 && chess[i][j + 3] == 2 && chess[i][j + 4] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,白方获胜");
				outtextxy(100, 100, str);
			}
		}
	}
	for (i = 0; i < 10; i++)		//横向检索
	{
		for (j = 0; j < 10; j++)
		{
			if (chess[j][i] == 1 && chess[j+1][i] == 1 && chess[j+2][i] == 1 && chess[j+3][i] == 1 && chess[j+4][i] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,黑方获胜");
				outtextxy(100, 100, str);
			}
			else if (chess[j][i] == 2 && chess[j + 1][i] == 2 && chess[j + 2][i] == 2 && chess[j + 3][i] == 2 && chess[j + 4][i] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,白方获胜");
				outtextxy(100, 100, str);
			}
		}
	}
	//斜左上搜索
	for (i = 0; i < 10; i++)
	{
		for (j = 15; j > 5; j--)
		{
			if (chess[j][i] == 1 && chess[j - 1][i+1] == 1 && chess[j - 2][i+2] == 1 && chess[j - 3][i+3] == 1 && chess[j - 4][i+4] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,黑方获胜");
				outtextxy(100, 100, str);
			}
			else if (chess[j][i] == 2 && chess[j - 1][i+1] == 2 && chess[j - 2][i+2] == 2 && chess[j-3][i+3] == 2 && chess[j - 4][i+4] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,白方获胜");
				outtextxy(100, 100, str);
			}
		}
	}
	//斜右上
	for (i = 0; i<15; i++)
	{
		for (j = 0; j <15; j++)
		{
			if (chess[j][i] == 1 && chess[j -1][i -1] == 1 && chess[j - 2][i - 2] == 1 && chess[j - 3][i - 3] == 1 && chess[j - 4][i - 4] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,黑方获胜");
				outtextxy(100, 100, str);
			}
			else if (chess[j][i] == 2 && chess[j - 1][i - 1] == 2 && chess[j - 2][i - 2] == 2 && chess[j - 3][i -3] == 2 && chess[j - 4][i - 4] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("宋体"));
				TCHAR str[30] = _T("游戏结束,白方获胜");
				outtextxy(100, 100, str);
			}
		}
	}
}
void playIt(void)					//执棋
{
	while (1)
	{
		
		if (KEY_DOWN(VK_UP) && cur.y > 45)
		{
			wipe(cur);
			cur.y -= 30;
			repaint(cur);
		}
		else if (KEY_DOWN(VK_LEFT) && cur.x > 45)
		{
			wipe(cur);
			cur.x -= 30;
			repaint(cur);
		}
		else if (KEY_DOWN(VK_DOWN) && cur.y < 405)
		{
			wipe(cur);
			cur.y += 30;
			repaint(cur);
		}
		else if (KEY_DOWN(VK_RIGHT) && cur.x < 405)
		{
			wipe(cur);
			cur.x += 30;
			repaint(cur);
		}
		if ((KEY_DOWN(VK_RETURN) || KEY_DOWN(VK_SPACE))&& chess[(cur.x - 15) / 30][(cur.y - 15) / 30] == 0)
		{
			if (sum % 2 == 1 )				//&&chess[(cur.x - 15) / 30][(cur.y - 15) / 30] == 0
			{
				chess[(cur.x - 15) / 30][(cur.y - 15) / 30] = 1;
				setlinecolor(BLACK);
				setfillcolor(BLACK);
				fillcircle(cur.x + 15, cur.y + 15, 13);
			}
			else if(sum % 2 == 0)			 //&& chess[(cur.x - 15) / 30][(cur.y - 15) / 30] == 0
			{
				chess[(cur.x - 15) / 30][(cur.y - 15) / 30] = 2;
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillcircle(cur.x + 15, cur.y + 15, 13);
			}
			sum++;
		}
		Sleep(100);						//放慢速度
		judge();
	}
}
void locate(void)					//确定自己下棋位置
{
	setcolor(RED);
	cur.x = 225;
	cur.y = 225;
	line(cur.x, cur.y, cur.x + 10, cur.y);
	line(cur.x, cur.y, cur.x, cur.y + 10);
	line(cur.x +30, cur.y+30, cur.x+20, cur.y+30);
	line(cur.x+30, cur.y+30, cur.x+30, cur.y+20);
	//rectangle(225, 225, 255, 255);
}

int main()
{
	showmap();
	locate();
	playIt();
	getchar();
    return 0;
}