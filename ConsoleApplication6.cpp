// ConsoleApplication6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int flag[50], flag1 = 0;
int D, N;
float r, dis;
typedef struct
{
	int x;
	int y;
}crocodile;
crocodile c[150];
void DFS(int i)
{
	r = D;
	flag[i] = 1;
	if ((50 - abs(c[i].x)) <= r || (50 - abs(c[i].y)) <= r)
	{
		printf("Yes\n");
		flag1 = 1;
		r = -1;
		return;
	}
	for (int j = 1; j <= N; j++)
	{
		dis = sqrt((c[j].x - c[i].x)*(c[j].x - c[i].x) + (c[j].y - c[i].y)*(c[j].y - c[i].y));
		if (dis <= r&&flag[j] != 1)
		{
			DFS(j);
		}
	}
}

int main()
{
	int i, j;
	scanf_s("%d %d", &N, &D);
	c[0].x = c[0].y = 0;
	for (i = 1; i <= N; i++)
		scanf("%d %d", &c[i].x, &c[i].y);
	r = 15.0 / 2 + D;
	i = 0;
	for (j = 1; j <= N; j++)
	{
		dis = sqrt((c[j].x - c[i].x)*(c[j].x - c[i].x) + (c[j].y - c[i].y)*(c[j].y - c[i].y));
		if (dis <= r&&flag[j] != 1)
		{
			DFS(j);
			r = 15.0 / 2 + D;
		}
	}
	if (flag1 == 0)
		printf("No\n");
    return 0;
}

