// ������.cpp : Defines the entry point for the console application.
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
void drawcursor(posType,COLORREF);//�ػ���

COLORREF colorArr[2]={RGB(0,0,0),RGB(255,255,255)};//������ɫ  �����

HWND hWnd;
int chess[20][20]={0};
int flag=0;
char name1[10],name2[10];
char control[10];//������ʽ
posType cur;//��ǰ�������λ��

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
	loadimage(NULL,"����.jpg");
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
	InputBox(name1, 10,"���������1(����)����\nȡ������","��ʾ","���1",0,0,0);
	InputBox(name2, 10,"���������2(����)����\nȡ������","��ʾ","���2",0,0,0);
	InputBox(control, 10,"�����������ʽ�����̻���꣩","��ʾ","���",0,0,true);//��ʽѡ��
	setbkmode(TRANSPARENT);
	char Name1[20],Name2[20];
	sprintf(Name1,"����: %s",name1);
	sprintf(Name2,"����: %s",name2);
	settextcolor(RED);
	outtextxy(520,20,Name1);
	settextcolor(BLUE);
	outtextxy(520,50,Name2);
	cur.x=250;
	cur.y=250;
	drawcursor(cur,RGB(0,0,0));//������
}

void gameplay()
{
//	if(control==���)
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
					MessageBox(hWnd,"�˴���������!","��ʾ",MB_OK);
					continue;
				}
				else
				{
					if(flag%2==0)
					{
					//	char information2[30];
					//	sprintf(information2,"��%s����",name2);
						setbkmode(TRANSPARENT);
						settextcolor(BLUE);
						outtextxy(520,200,"��       ����");
						setfillcolor(WHITE);
						solidcircle(550,205,10);
						setfillcolor(BLACK);
						solidcircle(x,y,10);
						chess[a][b]=1;
					}
					else
					{
					//	char information1[30];
					//	sprintf(information1,"��%s����",name1);
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						outtextxy(520,200,"��       ����");
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
				sprintf(result,"%sʤ��",name1);
				MessageBox(hWnd,result,"��Ϸ����",MB_OK);
				return;
			}
			else
			{
				char result[30];
				sprintf(result,"%sʤ��",name2);
				MessageBox(hWnd,result,"��Ϸ����",MB_OK);
				return;
			}
		}
	}
}

bool juge(int x,int y)
{
	int i,j;
	int t=2-flag%2;
	for(i=x-4,j=y;i<=x;i++)//��������
	{
		if(i>=1&&i<=16&&t==chess[i][j]&&t==chess[i+1][j]&&t==chess[i+2][j]&&t==chess[i+3][j]&&t==chess[i+4][j])
		{
			return true;
		}
	}
	for(i=x,j=y-4;j<=y;j++)//��������
	{
		if(j>=1&&j<=16&&t==chess[i][j]&&t==chess[i][j+1]&&t==chess[i][j+2]&&t==chess[i][j+3]&&t==chess[i][j+4])
		{
			return true;
		}
	}
	for(i=x-4,j=y-4;i<=x,j<=y;i++,j++)//б������1
	{
		if(i>=1&&i<=16&&j>=1&&j<=16&&t==chess[i][j]&&t==chess[i+1][j+1]&&t==chess[i+2][j+2]&&t==chess[i+3][j+3]&&t==chess[i+4][j+4])
		{
			return true;
		}
	}
	for(i=x+4,j=y-4;i>=x,j<=y;i--,j++)//б������2
	{
		if(i>=1&&i<=16&&j>=1&&j<=16&&t==chess[i][j]&&t==chess[i+1][j-1]&&t==chess[i+2][j-2]&&t==chess[i+3][j-3]&&t==chess[i+4][j-4])
		{
			return true;
		}
	}
	return false;
}

//�����ο�
void drawcursor(posType cur,COLORREF cl)
{
	setlinecolor(cl);
	rectangle(cur.x-13,cur.y-13,cur.x+13,cur.y+13);
}