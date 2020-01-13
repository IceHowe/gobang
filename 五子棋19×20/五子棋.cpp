// 五子棋.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
//#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

typedef struct position
{
	int x;
	int y;
} posType;

#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000)

void Init();
void gameplay();
bool juge(int x,int y);
void drawcursor(posType,COLORREF);//重绘光标

COLORREF colorArr[2]={RGB(0,0,0),RGB(255,255,255)};//矩形颜色  黑与白

HWND hWnd;
int chess[20][20]={0};
int flag=0;
char name1[10],name2[10];
char control[10];//操作方式
posType cur;//当前光标所在位置

int main(int argc, char* argv[])
{
	Init();
	gameplay();
	getch();
	closegraph();
	return 0;
}

void Init()
{
	initgraph(620,500);
//	setbkcolor(BLUE);
//	cleardevice();
	loadimage(NULL,"背景.jpg");
	mciSendString("open sky.mid alias music",NULL,0,NULL);
	mciSendString("play music",NULL,0,NULL);
	for(int i=2;i<20;i++)
	{	
		setlinecolor(BLACK);
		line(25,i*25,500,i*25);
		line(i*25,25,i*25,475);
	}
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID,2);
	line(25,25,500,25);
	line(25,475,500,475);
	line(25,25,25,475);
	line(500,25,500,475);
	InputBox(name1, 10,"请输入玩家1(黑棋)姓名\n取消则无","提示","玩家1",0,0,0);
	InputBox(name2, 10,"请输入玩家2(白棋)姓名\n取消则无","提示","玩家2",0,0,0);
	InputBox(control, 10,"请输入操作方式（键盘或鼠标）","提示","鼠标",0,0,true);//方式选择
	setbkmode(TRANSPARENT);
	char Name1[20],Name2[20];
	sprintf(Name1,"黑棋: %s",name1);
	sprintf(Name2,"白棋: %s",name2);
	settextcolor(RED);
	outtextxy(520,20,Name1);
	settextcolor(BLUE);
	outtextxy(520,50,Name2);
	cur.x=250;
	cur.y=250;
	drawcursor(cur,RGB(0,0,0));//操作框
}

void gameplay()
{
//	if(control==鼠标)
//	{
		MOUSEMSG m;
		int a=0;
		int b=0;
		int x,y;
		hWnd=GetHWnd();
		while(1)
		{
			m=GetMouseMsg();
			for(int i=1;i<=20;i++)
			{
				for(int j=1;j<20;j++)
				{
					if(abs(m.x-i*25)<12&&abs(m.y-j*25)<12)
					{
						a=i;
						b=j;
						x=i*25;
						y=j*25;
					}
				}
			}
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				if(chess[a][b]!=0)
				{
					MessageBox(hWnd,"此处已有棋子!","提示",MB_OK);
					continue;
				}
				else
				{
					if(flag%2==0)
					{
					//	char information2[30];
					//	sprintf(information2,"请%s下棋",name2);
						setbkmode(TRANSPARENT);
						settextcolor(BLUE);
						outtextxy(520,200,"请       下棋");
						setfillcolor(WHITE);
						solidcircle(550,205,10);
						setfillcolor(BLACK);
						solidcircle(x,y,10);
						chess[a][b]=1;
					}
					else
					{
					//	char information1[30];
					//	sprintf(information1,"请%s下棋",name1);
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						outtextxy(520,200,"请       下棋");
						setfillcolor(BLACK);
						solidcircle(550,205,10);
						setfillcolor(WHITE);
						solidcircle(x,y,10);
						chess[a][b]=2;
					}
				}
				flag++;
			}
//		}
		if(juge(a,b))
		{
			if(flag%2==1)
			{
				char result[30];
				sprintf(result,"%s胜利",name1);
				MessageBox(hWnd,result,"游戏结束",MB_OK);
				return;
			}
			else
			{
				char result[30];
				sprintf(result,"%s胜利",name2);
				MessageBox(hWnd,result,"游戏结束",MB_OK);
				return;
			}
		}
	}
}

bool juge(int x,int y)
{
	int i,j;
	int t=2-flag%2;
	for(i=x-4,j=y;i<=x;i++)//横向五子
	{
		if(i>=1&&i<=16&&t==chess[i][j]&&t==chess[i+1][j]&&t==chess[i+2][j]&&t==chess[i+3][j]&&t==chess[i+4][j])
		{
			return true;
		}
	}
	for(i=x,j=y-4;j<=y;j++)//纵向五子
	{
		if(j>=1&&j<=16&&t==chess[i][j]&&t==chess[i][j+1]&&t==chess[i][j+2]&&t==chess[i][j+3]&&t==chess[i][j+4])
		{
			return true;
		}
	}
	for(i=x-4,j=y-4;i<=x,j<=y;i++,j++)//斜向五子1
	{
		if(i>=1&&i<=16&&j>=1&&j<=16&&t==chess[i][j]&&t==chess[i+1][j+1]&&t==chess[i+2][j+2]&&t==chess[i+3][j+3]&&t==chess[i+4][j+4])
		{
			return true;
		}
	}
	for(i=x+4,j=y-4;i>=x,j<=y;i--,j++)//斜向五子2
	{
		if(i>=1&&i<=16&&j>=1&&j<=16&&t==chess[i][j]&&t==chess[i+1][j-1]&&t==chess[i+2][j-2]&&t==chess[i+3][j-3]&&t==chess[i+4][j-4])
		{
			return true;
		}
	}
	return false;
}

//画矩形框
void drawcursor(posType cur,COLORREF cl)
{
	setlinecolor(cl);
	rectangle(cur.x-13,cur.y-13,cur.x+13,cur.y+13);
}