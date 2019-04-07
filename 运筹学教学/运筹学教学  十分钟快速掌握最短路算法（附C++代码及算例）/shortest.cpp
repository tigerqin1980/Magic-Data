/*
Author: Hzoi_hexing
School: HuaZhong University of Science and Technology
Complier: g++.exe shortpath.cpp -o shortpath.exe -Ofast -std=c++11 -pg -g3 -I
SAMPLE INPUT:
n  m
7 11
x y z
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1
SAMPLE OUTPUT(全图最短路, 单源最短路可以按照输入提示输入st, ed进行检验)
0 5 5 3 4 1 6
5 0 4 2 6 6 1
5 4 0 3 7 4 3
3 2 3 0 7 4 3
4 6 7 7 0 3 5
1 6 4 4 3 0 7
6 1 3 3 5 7 0

*/ 

#include<bits/stdc++.h>
using namespace std;

int alg_mode; // 1: dijkstra, 2: spfa, 3: floyd(仅限于mode = 2，但是也可以求解 mode = 1)
int mode; // 1: 单源最短路 2: 全图最短路 

int n, m;// 点数，边数
int st, ed; // 起点，终点
int **G;
int *dis;
bool *vis;
const int INF = 0x3f3f3f3f;
int *path;

struct node{
	int data, id;
};

node make_node(int x, int y){
	node cc;
	cc.id = x; cc.data = y;
	return cc;
}//形成点 

typedef vector<node> NODE;
NODE *graph;// 存储图结构

void initlization(){//初始化 
	printf("input the number of nodes and edges, format:\nn m\n");
	scanf("%d %d", &n, &m);
	graph = new NODE[n + 5];
	G = new int*[n + 5];
	dis = new int[n + 5];
	vis = new bool[n + 5];
	path = new int[n + 5];
	for (int i = 1; i <= n; i ++){
		path[i] = i;
		G[i] = new int[n + 5];
		for (int j = 1; j <= n; j ++)
			G[i][j] = INF;
		G[i][i] = 0;
	}
	printf("input the information of graph in next m lines, format:\nx y z\n");
	printf("which means there is a edge form x(1..n) to y(1..n) whose weight is z\n");
	int x, y, z;
	for (int i = 0; i < m; i ++){
		scanf("%d %d %d", &x, &y, &z);
		graph[x].push_back(make_node(y, z));
		graph[y].push_back(make_node(x, z));
		G[x][y] = G[y][x] = min(G[x][y], z);
	}//无向图 
	printf("input the solution mode: 1.Single source shortest path, 2:Total line shortest path\n");
	scanf("%d", &mode);
	printf("input algorithm mode:1: dijkstra, 2: spfa, 3: floyd(only for mode = 2, but mode = 1 is ok\n");
	scanf("%d", &alg_mode);
}

void dijkstra(int st){
	for (int i = 1; i <= n; i ++)
		vis[i] = 0, dis[i] = INF, path[i] = i != st ? -1 : st;
	dis[st] = 0;//到自身距离为0 
	int min_dis = INF, x;
	for (int i = 1; i <= n; i ++){
		x = 0;
		min_dis = INF;
		for (int j = 1; j <= n; j ++){
			if (dis[j] < min_dis && !vis[j]){
				min_dis = dis[j];
				x = j;
			}// 选择从起点出发最短的点 
		}
		vis[x] = 1;
		NODE::iterator it = graph[x].begin();
		for (; it != graph[x].end(); it ++){
			int y = it->id;
			if (!vis[y] && dis[y] > dis[x] + it->data){//松弛操作 
				dis[y] = dis[x] + it->data;
				path[y] = x;// 记录路径 
			}//松弛操作 ，利用三角不等式 
		}
	}
 	return;
}

void spfa(int st){
	map<int, int> inq;
	for (int i = 1; i <= n; i ++)
		vis[i] = 0, dis[i] = INF, inq[i] = 0, path[i] = i != st ? -1 : st;
	dis[st] = 0;//到自身距离为0 
	queue <int> Q;
	while (Q.size()) Q.pop();
	vis[st] = 1;
	Q.push(st);
	while (Q.size()){
		int x = Q.front();
		Q.pop();
		vis[x] = 0;
		NODE::iterator it = graph[x].begin();
		for (; it != graph[x].end(); it ++){
			int y = it->id;
			if (dis[y] > dis[x] + it->data){//松弛操作 
				dis[y] = dis[x] + it->data;
				path[y] = x;// 记录路径 
			}else continue;//松弛操作 ，利用三角不等式 
			if (!vis[y]){// 如果y没有在队列中，则加入队列 
				Q.push(y);
				vis[y] = 1;
				inq[y] = inq[y] + 1;
				if (inq[y] >= n){// 判断负环 
					printf("there is a negative circle!\n");
					assert(inq[y] < n);
				} 
			}
		}
	}
	return;
}

void floyd(){
	for (int k = 1; k <= n; k ++)//枚举中间结点 
		for (int i = 1; i <= n; i ++){
			if (i != k){
				for (int j = 1; j <= n; j ++){
					if (i != j && j != k){
						G[i][j] = min(G[i][j], G[i][k] + G[k][j]);//floyd 
					}
				}
			}
		}
}

void print(int st, int ed){
	stack<int> answer;
	while (answer.size()) answer.pop();
	answer.push(ed);
	for (int i = path[ed]; i != st; i = path[i]){
		answer.push(i);
	} 
	printf("%d", st);
	while (answer.size()){
		printf("->%d", answer.top());
		answer.pop();
	}
	printf("\n");
}//输出最短路径 

int main(){
	initlization();
	if (mode == 2){// 求全图最短路 
		switch (alg_mode){
			case 1:{
				for (int i = 1; i <= n; i ++){
					dijkstra(i);
					for (int j = 1; j <= n; j ++){
						printf("%d ", dis[j]);
					}
					printf("\n");
				}			
				break;
			}
			case 2:{
				for (int i = 1; i <= n; i ++){
					spfa(i);
					for (int j = 1; j <= n; j ++){
						printf("%d ", dis[j]);
					}
					printf("\n");
				}	
				break;
			}
			case 3:{
				floyd();
				for (int i = 1; i <= n; i ++){
					for (int j = 1; j <= n; j ++){
						printf("%d ", G[i][j]);
					}
					printf("\n");
				}	
				break;
			}
			default:{
				printf("Error!\n");
				break;
			}
		}
	}else if (mode == 1){// 单源最短路径 
		printf("input the start city and end city, format:\nst ed\n");
		scanf("%d %d", &st, &ed);
		switch (alg_mode){
			case 1:{
				dijkstra(st);
				printf("%d\n", dis[ed]);
				print(st, ed);
				break;
			}
			case 2:{
				spfa(st);
				printf("%d\n", dis[ed]);
				print(st, ed);
				break;
			}
			case 3:{
				floyd();
				printf("%d\n", G[st][ed]);
				print(st, ed);
				break;
			}
			default:{
				printf("Error!\n");
				break;
			}
		}
	}
	return 0; 
}