// ConsoleApplication4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#define N 15
void ListComponentsWithDFS();
void ListComponentsWithBFS();
void DFS(int V);
void BFS(int V);
void InitVisit(void);
int n;
bool Visited[N];
int G[N][N] = { 0 };

int main()
{
	int E;
	scanf("%d %d", &n, &E);
	for (int i = 0; i < E; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		G[b][a] = G[a][b] = 1;
	}
	InitVisit();
	ListComponentsWithDFS();
	InitVisit();
	ListComponentsWithBFS();
    return 0;
}

void ListComponentsWithDFS()
{
	for (int V = 0; V < n;V++)
		if (!Visited[V])
		{
			printf("{ ");
			DFS(V);
			printf("}\n");
		}
}
void ListComponentsWithBFS()
{
	for (int V = 0; V < n; V++)
		if (!Visited[V])
		{
			printf("{ ");
			BFS(V);
			printf("}\n");
		}
}
void DFS(int V)
{
	Visited[V] = true;
	printf("%d", V);
	for (int i = 0; i < n; i++)
	{
		if (G[V][i] && !Visited[i])
			DFS(i);
	}
}
void BFS(int V)
{
	const int MAX_SIZE = 100;
	int Queue[MAX_SIZE];
	int first = -1, last = -1;
	Queue[++last] = V;
	Visited[V] = true;
	while (first < last)
	{
		int F = Queue[++first];
		printf("%d", F);
		for (int i = 0; i < n; i++)
		{
			if (G[F][i] && !Visited[i])
			{
				Queue[++last] = i;
				Visited[i] = true;
			}
		}
	}
}
void InitVisit()
{
	for (int i = 0; i < N; i++)
		Visited[i] = false;
}

