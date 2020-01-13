// ������others.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#define KEY_DOWN(vk_c)(GetAsyncKeyState(vk_c)&0x8000)	//�����ϵĻس���Ӧ
typedef struct position {
	int x;				//���̵�x����
	int y;				//���̵�y����
}postype;
postype cur;			//���ӵ��е��������15
int sum=1;				//�ܹ��߹��Ĳ���
//COLORREF colorarr[2] = { RGB(249,214,91),RGB(255,0,0)};
//postype ballsarr[255];	//��������������
COLORREF c1;				//��ʾc1������������ɫ
int index = 5;
int chess[15][15] = { 0 };		//��ʾÿ��������ݣ�������Ϊ0������Ϊ1������Ϊ2
void showmap(void)		//��������
{
	initgraph(510, 510);
	setbkcolor(RGB(249,214,91));
	cleardevice();		//������������ʹ����ɫ����
	setlinecolor(BLACK);	//������ɫΪ��
	for (int i = 1; i < 16; i++)	//����
	{	
		line(30 , 30 * i, 15 * 30, 30 * i);
	}
	for ( i = 1; i < 16; i++)	//����
	{
		line(30*i , 30,  30 * i , 15 * 30);
	}
}
void wipe(postype)				//�������������ɹ��
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
//���㷨���ж��µ�λ�õĸ�����������Ƿ񹹳�����
void judge()
{
	int i, j;
	for (i = 0; i < 10; i++)		//�������
	{
		for (j = 0; j < 10; j++)
		{
			if (chess[i][j] == 1 && chess[i][j + 1] == 1 && chess[i][j + 2] == 1 && chess[i][j + 3] == 1 && chess[i][j + 4] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�ڷ���ʤ");
				outtextxy(100, 100, str);
			}
			else if (chess[i][j] == 2 && chess[i][j + 1] == 2 && chess[i][j + 2] == 2 && chess[i][j + 3] == 2 && chess[i][j + 4] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�׷���ʤ");
				outtextxy(100, 100, str);
			}
		}
	}
	for (i = 0; i < 10; i++)		//�������
	{
		for (j = 0; j < 10; j++)
		{
			if (chess[j][i] == 1 && chess[j+1][i] == 1 && chess[j+2][i] == 1 && chess[j+3][i] == 1 && chess[j+4][i] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�ڷ���ʤ");
				outtextxy(100, 100, str);
			}
			else if (chess[j][i] == 2 && chess[j + 1][i] == 2 && chess[j + 2][i] == 2 && chess[j + 3][i] == 2 && chess[j + 4][i] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�׷���ʤ");
				outtextxy(100, 100, str);
			}
		}
	}
	//б��������
	for (i = 0; i < 10; i++)
	{
		for (j = 15; j > 5; j--)
		{
			if (chess[j][i] == 1 && chess[j - 1][i+1] == 1 && chess[j - 2][i+2] == 1 && chess[j - 3][i+3] == 1 && chess[j - 4][i+4] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�ڷ���ʤ");
				outtextxy(100, 100, str);
			}
			else if (chess[j][i] == 2 && chess[j - 1][i+1] == 2 && chess[j - 2][i+2] == 2 && chess[j-3][i+3] == 2 && chess[j - 4][i+4] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�׷���ʤ");
				outtextxy(100, 100, str);
			}
		}
	}
	//б����
	for (i = 0; i<15; i++)
	{
		for (j = 0; j <15; j++)
		{
			if (chess[j][i] == 1 && chess[j -1][i -1] == 1 && chess[j - 2][i - 2] == 1 && chess[j - 3][i - 3] == 1 && chess[j - 4][i - 4] == 1)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�ڷ���ʤ");
				outtextxy(100, 100, str);
			}
			else if (chess[j][i] == 2 && chess[j - 1][i - 1] == 2 && chess[j - 2][i - 2] == 2 && chess[j - 3][i -3] == 2 && chess[j - 4][i - 4] == 2)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("����"));
				TCHAR str[30] = _T("��Ϸ����,�׷���ʤ");
				outtextxy(100, 100, str);
			}
		}
	}
}
void playIt(void)					//ִ��
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
		Sleep(100);						//�����ٶ�
		judge();
	}
}
void locate(void)					//ȷ���Լ�����λ��
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