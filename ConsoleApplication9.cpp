// ConsoleApplication9.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#define INF 501;
int dist[501];
int map[501][501];
int cost[501][501];
int MCost[501];
int visited[501] = { 0 };
void dijkstra(int v0, int v, int d)
{
	dist[v0] = 0; visited[v0] = 1;
	int i, w;
	for (i = 1; i < v; i++)
	{
		int min = INF;
		for (w = 0; w < v; w++)
		{
			if (!visited[w])
			{
				if (dist[w] < min)
				{
					min = dist[w];
					v0 = w;
				}
			}
		}
		visited[v0] = 1;
		for (w = 0; w < v; w++)
		{
			if (!visited[w] && min + map[v0][w] < dist[w])
			{
				dist[w] = min + map[v0][w];
				MCost[w] = MCost[v0] + cost[v0][w];
			}
			else if (!visited[w] && min + map[v0][w] == dist[w] && MCost[w]>MCost[v0] + cost[v0][w])
				MCost[w] = MCost[v0] + cost[v0][w];
		}
	}
}

int main()
{
	int v, e, s, d;
	cin >> v >> e >> s >> d;
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			map[i][j] = map[j][i] = INF;
			cost[i][j] = cost[j][i] = INF;
		}
	}
	for (int i = 0; i < e; i++)
	{
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			map[a][b] = map[b][a] = c;
			cost[a][b] = cost[b][a] = d;
	}
	for (int i = 0; i < v; i++)
	{
			dist[i] = map[i][s];
			MCost[i] = cost[i][s];
	}
	dijkstra(s, v, d);
	cout << dist[d] << " " << MCost[d] << endl;
    return 0;
}