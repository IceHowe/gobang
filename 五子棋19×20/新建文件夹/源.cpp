/*
初始化游戏界面：
1.绘图环境
2.背景图片
3.背景音乐
4.绘制格子
5.绘制边界线
6.显示黑棋为玩家1，白棋为玩家2

下棋：
1.while循环让游戏能不断的玩下去
2.定义一个保存鼠标消息的变量，获取鼠标消息
3.鼠标左键按下的时候下棋
4.探讨怎样实现玩家轮流下棋
5.探讨怎样让玩家在十字交叉的位置下棋
6.解决同位置可以反复下棋的问题
*/
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

#define N	20

int chess[N][N] = { 0 };
//用来记录轮到玩家1还是玩家2
int flag = 0;

void initGame();
void playChess();
int judge(int, int);

HWND hWnd;

int main()
{
	//初始化游戏
	initGame();
	playChess();
		
	return 0;
}

void initGame()
{
	initgraph(600, 500);
		setbkcolor(BLUE);
	cleardevice();
//	loadimage(NULL, L"1.jpg");

	//绘制棋盘
	for (int i = 1; i < 20; i++)
	{
		setlinestyle(PS_SOLID, 1);
		setlinecolor(BLACK);
		line(i * 25, 0, i * 25, 500);
		line(0, i * 25, 500, i * 25);
	}
	//绘制棋盘边界线
	setlinestyle(PS_SOLID, 2);
	line(500, 0, 500, 500);
	line(0, 500, 500, 500);

	outtextxy(505, 20, "黑棋：玩家1");
	outtextxy(505, 50, "白棋：玩家2");
}

void playChess()
{
	int a = 0, b = 0;
	int x, y;
	MOUSEMSG m;
	hWnd = GetHWnd();
	while (1)
	{
		m = GetMouseMsg();//获取鼠标消息
		for (int i = 1; i < 20; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)
				{
					a = i;
					b = j;
					x = i * 25;
					y = j * 25;
				}
			}
		}
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (chess[a][b] != 0)
			{
				MessageBox(hWnd, "这里已经有棋子了，请重新选择下棋的位置", "提示", MB_OK);
				continue;
			}
			else
			{
				if (flag % 2 == 0)
				{
					outtextxy(505, 200, "请玩家2落子");
					setfillcolor(BLACK);
					solidcircle(x, y, 10);
					chess[a][b] = 1;
				}
				else
				{
					outtextxy(505, 200, "请玩家1落子");
					setfillcolor(WHITE);
					solidcircle(x, y, 10);
					chess[a][b] = 2;
				}
			}

			flag++;
		}
		if (judge(a, b))
		{
			if (1 == flag % 2)
			{
				MessageBox(hWnd, "玩家1胜利", "游戏结束", MB_OK);
				return;	//修复BUG 
			}
			else
			{
				MessageBox(hWnd, "玩家2胜利", "游戏结束", MB_OK);
				return;	//修复BUG 
			}
		}
	}
}



int judge(int x, int y)
{
	int i, j;
	int t = 2 - flag % 2;//flag%2=0时，t=2
	for (i = x - 4, j = y; i <= x; i++)
	{
		if (i >= 1 && i <= N - 4 && t == chess[i][j] && t == chess[i + 1][j] && t == chess[i + 2][j] && t == chess[i + 3][j] && t == chess[i + 4][j])
			return 1;
	}
	for (i = x, j = y - 4; j <= y; j++)
	{
		if (j >= 1 && j <= N - 4 && t == chess[i][j] && t == chess[i][j + 1] && t == chess[i][j + 2] && t == chess[i][j + 3] && t == chess[i][j + 4])
			return 1;
	}
	for (i = x - 4, j = y - 4; i <= x, j <= y; i++, j++)
	{
		if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 && t == chess[i][j] && t == chess[i + 1][j + 1] && t == chess[i + 2][j + 2] && t == chess[i + 3][j + 3] && t == chess[i + 4][j + 4])
			return 1;
	}
	for (i = x - 4, j = y + 4; i <= x, j >= 1; i++, j--)
	{
		if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 && t == chess[i][j] && t == chess[i + 1][j - 1] && t == chess[i + 2][j - 2] && t == chess[i + 3][j - 3] && t == chess[i + 4][j - 4])
			return 1;
	}
	return 0;
}