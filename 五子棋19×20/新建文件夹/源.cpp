/*
��ʼ����Ϸ���棺
1.��ͼ����
2.����ͼƬ
3.��������
4.���Ƹ���
5.���Ʊ߽���
6.��ʾ����Ϊ���1������Ϊ���2

���壺
1.whileѭ������Ϸ�ܲ��ϵ�����ȥ
2.����һ�����������Ϣ�ı�������ȡ�����Ϣ
3.���������µ�ʱ������
4.̽������ʵ�������������
5.̽�������������ʮ�ֽ����λ������
6.���ͬλ�ÿ��Է������������
*/
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

#define N	20

int chess[N][N] = { 0 };
//������¼�ֵ����1�������2
int flag = 0;

void initGame();
void playChess();
int judge(int, int);

HWND hWnd;

int main()
{
	//��ʼ����Ϸ
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

	//��������
	for (int i = 1; i < 20; i++)
	{
		setlinestyle(PS_SOLID, 1);
		setlinecolor(BLACK);
		line(i * 25, 0, i * 25, 500);
		line(0, i * 25, 500, i * 25);
	}
	//�������̱߽���
	setlinestyle(PS_SOLID, 2);
	line(500, 0, 500, 500);
	line(0, 500, 500, 500);

	outtextxy(505, 20, "���壺���1");
	outtextxy(505, 50, "���壺���2");
}

void playChess()
{
	int a = 0, b = 0;
	int x, y;
	MOUSEMSG m;
	hWnd = GetHWnd();
	while (1)
	{
		m = GetMouseMsg();//��ȡ�����Ϣ
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
				MessageBox(hWnd, "�����Ѿ��������ˣ�������ѡ�������λ��", "��ʾ", MB_OK);
				continue;
			}
			else
			{
				if (flag % 2 == 0)
				{
					outtextxy(505, 200, "�����2����");
					setfillcolor(BLACK);
					solidcircle(x, y, 10);
					chess[a][b] = 1;
				}
				else
				{
					outtextxy(505, 200, "�����1����");
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
				MessageBox(hWnd, "���1ʤ��", "��Ϸ����", MB_OK);
				return;	//�޸�BUG 
			}
			else
			{
				MessageBox(hWnd, "���2ʤ��", "��Ϸ����", MB_OK);
				return;	//�޸�BUG 
			}
		}
	}
}



int judge(int x, int y)
{
	int i, j;
	int t = 2 - flag % 2;//flag%2=0ʱ��t=2
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