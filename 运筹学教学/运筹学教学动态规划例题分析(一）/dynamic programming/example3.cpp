/*
sample input:
10 5
1 0
3 1 2 3
3 4 5 6
2 7 8
1 9
550 900 770
680 790 1050
580 760 660
510 700 830
610 790
540 940
790 270
1030
1390
*/



#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

int **dp;// dp方程 
int **graph;// 从至表 
int N, T;// 城市数量以及阶段数量 
int *fa;// 记录上一个访问。 
typedef vector<int> List;
List *Nodes;

void print(int x){
	if (x == fa[x]){
		printf("%d ", x);
		return;
	}else{
		print(fa[x]);
		printf("%d ", x);
	}
}

int main(){
	scanf("%d %d", &N, &T);
	
	dp = new int*[T];
	for (int i = 0; i < T; i ++){
		dp[i] = new int[N];
		for (int j = 0; j < N; j ++) dp[i][j] = INF;
	}
	
	Nodes = new List[T];
	int m, x;
	for (int i = 0; i < T; i ++){
		scanf("%d", &m);
		Nodes[i].clear();
		for (int j = 0; j < m; j ++){
			scanf("%d", &x);
			Nodes[i].push_back(x);
		}
	}
	
	graph = new int*[N];
	fa = new int[N];
	for (int i = 0; i < N; i ++){
		graph[i] = new int[N];
		fa[i] = i;
		for (int j = 0; j < N; j ++){
			graph[i][j] = INF;
		}
	}
	
	for (int i = 0; i < T - 1; i ++){
		int sz_1 = Nodes[i].size(), sz_2 = Nodes[i + 1].size();
		for (int j = 0; j < sz_1; j ++){
			for (int k = 0; k < sz_2; k ++){
				scanf("%d", &graph[Nodes[i][j]][Nodes[i + 1][k]]);
			}
		}
	}
	
	for (int i = 0; i < Nodes[0].size(); i ++) dp[0][Nodes[0][i]] = 0;
	for (int i = 1; i < T; i ++){
		int sz_1 = Nodes[i].size(), sz_2 = Nodes[i - 1].size();
		for (int j = 0; j < sz_1; j ++){
			int x = Nodes[i][j];
			for (int k = 0; k < sz_2; k ++){
				int y = Nodes[i - 1][k];
				//dp[i][x] = min(dp[i][x], dp[i - 1][y] + graph[y][x]);
				if (dp[i][x] > dp[i - 1][y] + graph[y][x]){
					dp[i][x] = dp[i - 1][y] + graph[y][x];
					fa[x] = y;
				}
			}
		}
	}
	for (int i = 0; i < Nodes[T - 1].size(); i ++){
		printf("target = %d, path:", dp[T - 1][Nodes[T - 1][i]]);
		int x = Nodes[T - 1][i];
		print(x);
		printf("\n");
	}
}
