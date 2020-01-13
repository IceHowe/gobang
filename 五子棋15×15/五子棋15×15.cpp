
// 五子棋1.cpp : Defines the entry point for the console application.
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
void Mousegameplay();
void Boardgameplay();
bool juge(int x,int y);
void drawcursor(posType,COLORREF);//重绘光标
void drawline();
void drawchess(int chess[16][16]);

COLORREF colorArr[2]={RGB(0,0,0),RGB(255,255,255)};//矩形颜色  黑与白

HWND hWnd;
int chess[16][16]={0};
int flag=0;
char name1[10],name2[10];
char control[10];//操作方式
posType cur;//当前光标所在位置
char* Mouse="鼠标";
char* Board="键盘";
char Name1[20],Name2[20];
char choose[10];
char* again="是";

int main(int argc, char* argv[])
{
	while(1)
	{
	Init();
	if(strcmp(control,Board)==0)
		Boardgameplay();
	else
		Mousegameplay();
	getch();
	closegraph();
	InputBox(choose,10,"是否再来一局","提示","是",0,0,0);
	if(strcmp(choose,again)!=0){
	break;
	}
	else
	{
		flag=0;
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				chess[i][j]=0;
			}
		}
	}
	}
	return 0;
}

void Init()
{
	initgraph(760,640);	
	setbkcolor(RGB(240,153,24));
	cleardevice();
//	loadimage(NULL,"F:\\FFOutput\\格式工厂桃花.jpg");
	mciSendString("open sky.mid alias music",NULL,0,NULL);
	mciSendString("play music",NULL,0,NULL);
	for(int i=2;i<=15;i++)
	{	
		setlinecolor(BLACK);
		line(40,i*40,600,i*40);
		line(i*40,40,i*40,600);
	}
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID,2);
	line(40,40,600,40);
	line(40,600,600,600);
	line(40,40,40,600);
	line(600,40,600,600);
	InputBox(name1, 10,"请输入玩家1(黑棋)姓名\n取消则无","提示","玩家1",0,0,true);
	InputBox(name2, 10,"请输入玩家2(白棋)姓名\n取消则无","提示","玩家2",0,0,true);
	InputBox(control, 10,"请输入操作方式（键盘或鼠标）","提示","鼠标",0,0,true);//方式选择
	setbkmode(TRANSPARENT);
//	char Name1[20],Name2[20];   转为全局变量
	sprintf(Name1,"黑棋: %s",name1);
	sprintf(Name2,"白棋: %s",name2);
	settextcolor(RED);
	outtextxy(620,40,Name1);
	settextcolor(BLUE);
	outtextxy(620,60,Name2);
}

void Mousegameplay()
{
	MOUSEMSG m;
	int a=0;
	int b=0;
	int x,y;
	hWnd=GetHWnd();
	while(1)
	{
		m=GetMouseMsg();
		for(int i=1;i<=15;i++)
		{
			for(int j=1;j<=15;j++)
			{
				if(abs(m.x-i*40)<20&&abs(m.y-j*40)<20)
				{
					a=i;
					b=j;
					x=i*40;
					y=j*40;
				}
			}
		}//for结束
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
					outtextxy(620,200,"请       下棋");
					setfillcolor(WHITE);
					solidcircle(650,205,10);
					setfillcolor(BLACK);
					solidcircle(x,y,20);
					chess[a][b]=1;
				}
				else
				{
				//	char information1[30];
				//	sprintf(information1,"请%s下棋",name1);
					setbkmode(TRANSPARENT);
					settextcolor(RED);
					outtextxy(620,200,"请       下棋");
					setfillcolor(BLACK);
					solidcircle(650,205,10);
					setfillcolor(WHITE);
					solidcircle(x,y,20);
					chess[a][b]=2;
				}
			}
			flag++;
		}//if鼠标按下结束
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
		}//if获胜判断结束
	}//while结束
}

void Boardgameplay()
{
	hWnd=GetHWnd();
	char c;
	cur.x=320;
	cur.y=320;
	drawcursor(cur,RGB(0,0,0));//操作框
	while(1)
	{
		if(flag%2==0)//黑棋
		{
			while(1)
			{
//				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				if(kbhit())c=getch();
				if(c=='w'||c=='W')
				{
					if(cur.y>40)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.y-=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						outtextxy(620,200,"请       下棋");
						setfillcolor(BLACK);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(c=='s'||c=='W')
				{
					if(cur.y<600)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.y+=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						outtextxy(620,200,"请       下棋");
						setfillcolor(BLACK);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(c=='a'||c=='A')
				{
					if(cur.x>40)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.x-=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						outtextxy(620,200,"请       下棋");
						setfillcolor(BLACK);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(c=='d'||c=='D')
				{
					if(cur.x<600)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.x+=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						outtextxy(620,200,"请       下棋");
						setfillcolor(BLACK);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(KEY_DOWN(VK_RETURN))
				{
					if(chess[cur.x/40][cur.y/40]!=0){
						MessageBox(hWnd,"此处已有棋子!","提示",MB_OK);
						continue;
					}
					setfillcolor(BLACK);
					solidcircle(cur.x,cur.y,20);
					chess[cur.x/40][cur.y/40]=1;
					setbkmode(TRANSPARENT);
					settextcolor(BLUE);
					outtextxy(620,200,"请       下棋");
					setfillcolor(WHITE);
					solidcircle(650,205,10);
					Sleep(200);
					break;
				}
				if(juge(cur.x/40,cur.y/40))
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
				}//if获胜判断结束
				c=0;
			}//while结束
		}//if黑棋
		else if(flag%2==1)//白棋
		{
			while(1)
			{
				if(KEY_DOWN(VK_UP))
				{
					if(cur.y>40)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.y-=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(BLUE);
						outtextxy(620,200,"请       下棋");
						setfillcolor(WHITE);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(KEY_DOWN(VK_DOWN))
				{
					if(cur.y<600)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.y+=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(BLUE);
						outtextxy(620,200,"请       下棋");
						setfillcolor(WHITE);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(KEY_DOWN(VK_LEFT))
				{
					if(cur.x>40)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.x-=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(BLUE);
						outtextxy(620,200,"请       下棋");
						setfillcolor(WHITE);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(KEY_DOWN(VK_RIGHT))
				{
					if(cur.x<600)
					{
						cleardevice();
						drawline();
						drawchess(chess);
						cur.x+=40;
						drawcursor(cur,RGB(0,0,0));
						setbkmode(TRANSPARENT);
						settextcolor(BLUE);
						outtextxy(620,200,"请       下棋");
						setfillcolor(WHITE);
						solidcircle(650,205,10);
					}
					else
					{//越界音效
					}
				}
				else if(KEY_DOWN(VK_RETURN))
				{
					if(chess[cur.x/40][cur.y/40]!=0){
						MessageBox(hWnd,"此处已有棋子!","提示",MB_OK);
						continue;
					}
					setfillcolor(WHITE);
					solidcircle(cur.x,cur.y,20);
					chess[cur.x/40][cur.y/40]=2;
					setbkmode(TRANSPARENT);
					settextcolor(RED);
					outtextxy(620,200,"请       下棋");
					setfillcolor(BLACK);
					solidcircle(650,205,10);
					c=0;
					Sleep(200);
					break;
				}
				if(juge(cur.x/40,cur.y/40))
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
				}//if获胜判断结束
				Sleep(100);
//				c=0;
			}//while结束
		}//if白棋
		flag++;
		c=0;
	}//外部while(1)结束
}

bool juge(int x,int y)
{
	int i,j;
	int t=2-flag%2;
	for(i=x-4,j=y;i<=x;i++)//横向五子
	{
		if(i>=1&&i<=11&&t==chess[i][j]&&t==chess[i+1][j]&&t==chess[i+2][j]&&t==chess[i+3][j]&&t==chess[i+4][j])
		{
			return true;
		}
	}
	for(i=x,j=y-4;j<=y;j++)//纵向五子
	{
		if(j>=1&&j<=11&&t==chess[i][j]&&t==chess[i][j+1]&&t==chess[i][j+2]&&t==chess[i][j+3]&&t==chess[i][j+4])
		{
			return true;
		}
	}
	for(i=x-4,j=y-4;i<=x,j<=y;i++,j++)//斜向五子左上至右下
	{
		if(i>=1&&i<=11&&j>=1&&j<=11&&t==chess[i][j]&&t==chess[i+1][j+1]&&t==chess[i+2][j+2]&&t==chess[i+3][j+3]&&t==chess[i+4][j+4])
		{
			return true;
		}
	}
	for(i=x-4,j=y+4;i<=x,j>=y;i++,j--)//斜向五子右上至左下
	{
		if(i>=1&&i<=15&&j>=1&&j<=15&&t==chess[i][j]&&t==chess[i+1][j-1]&&t==chess[i+2][j-2]&&t==chess[i+3][j-3]&&t==chess[i+4][j-4])
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
	rectangle(cur.x-20,cur.y-20,cur.x+20,cur.y+20);
}

//重绘棋盘
void drawline()
{
	for(int i=2;i<=15;i++)
	{	
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID,1);
		line(40,i*40,600,i*40);
		line(i*40,40,i*40,600);
	}
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID,2);
	line(40,40,600,40);
	line(40,600,600,600);
	line(40,40,40,600);
	line(600,40,600,600);
	settextcolor(RED);
	outtextxy(620,40,Name1);
	settextcolor(BLUE);
	outtextxy(620,60,Name2);
}

//恢复棋局
void drawchess(int chess[16][16])
{
//	posType temp;
//	temp.x=40;
//	temp.y=40;
	for(int i=1;i<16;i++){
		for(int j=1;j<16;j++){
			if(chess[i][j]==1){
				setfillcolor(BLACK);
				solidcircle(i*40,j*40,20);
			}
			if(chess[i][j]==2){
				setfillcolor(WHITE);
				solidcircle(i*40,j*40,20);
			}
		}
	}
}