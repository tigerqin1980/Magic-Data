//*
Author: Xing He
School: HuaZhong University of Science and Techonlogy
Complier: g++.exe maxflow.cpp -o maxflow.exe -std=c++11 -Ofast
Time: 2017-09

输入格式：
首先输入两个整数n, m分布代表节点数和边数，接下来m行，每行3个整数x y z
代表x y之间路径的容量是z
输出格式
一个整数最大流 

 
Input
6 9
1 2 8
1 3 7
2 4 9
2 5 3
2 3 5
3 5 9
4 6 7
5 4 6
5 6 10
Output:
15


*/ 

#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;//无穷大
int **edge; //每个边的容量限制 
bool *visited;// 宽搜的标记数组
int *father; //  father[i]表示i节点的前驱 
struct arr{
	int tt, ww, next;
}*c;//邻接表 
int *r;// 使用数组模拟邻接表，方便之后的运算 
int *d;
int tot;//边的数量 
int m, n;//边数，点数 
int alg_mode = 1; // 算法模式： 1.dinic 2.EK 
void add(int x, int y, int z){
	c[++ tot].tt = y;
	c[tot].ww = z;
	c[tot].next = r[x];
	r[x] = tot;
	return;
}//建边，数组模拟链表 

bool bfs(int s, int t){//宽搜，分层 
	int h = 0,ti = 0;	
	int *q = new int[n + 5];
	int qm = n + 5;
	for (int i = 1; i <= n; i ++)
		d[i] = 0;
	q[++ti] = s;
	d[s] = 1;
	
	while (h != ti){
		h = (h % qm) + 1;
		int x = q[h];
		for (int i = r[x]; i; i = c[i].next){
			int y = c[i].tt;
			if (!d[y] && c[i].ww > 0){
				ti = (ti % qm) + 1;
				q[ti] = y;
				d[y] = d[x] + 1;
				if (y == t) return 1;
			}
		}
	}
	return 0;
}

int dinic(int x, int f, int t){
	if (x == t) return f;
	int temp = 0,k;
	for (int i = r[x]; i; i = c[i].next){
		int y = c[i].tt;
		if (c[i].ww > 0 && d[y] == d[x] + 1 && f - temp > 0){
			k = dinic(y, min(f - temp, c[i].ww), t);
			if (k == 0) d[y] = 0;
			c[i].ww -=k;
			c[i ^ 1].ww +=k;// 前向弧减去 后向弧加上 
			temp +=k;
		}
	}
	return temp;
}

int EK(){  
	int ans = 0;
    while(1){  
    	int M = n, N = m;
        queue <int> q;//队列  
        visited = new bool[n + 5];
        father = new int[n + 5];
		for (int i = 0; i < n + 5; i ++){
        	visited[i] = false;//清空，把vistied清空为0
        	father[i] = -1;//把father变成空 
        }
        
        int now;  
        visited[0] = true;  
        q.push(0); 
		//宽度优先级搜索，寻找上层节点 
        while(!q.empty()){  
            now = q.front();  
            q.pop();  
            if(now == M - 1) break;  
            for(int i = 0; i < M; i++){  
                if(edge[now][i] && !visited[i]){ 
                    father[i] = now;  
                    visited[i] = true;  
                    q.push(i);  
                }  
            }  
        }  
        if(!visited[M - 1]) break; //没有可以到达汇点的增广路
        int u, Min = INF; 
        for(u = M-1; u; u = father[u]){  
            if(edge[father[u]][u] < Min)  
                Min = edge[father[u]][u];  
        }  //寻找最小限制流量的边 
        for(u = M - 1; u; u = father[u]){  
            edge[father[u]][u] -= Min;  
            edge[u][father[u]] += Min;  
        }// 前向弧减去 后向弧加上     
		//当前增广路径增加的流 
        ans += Min;  
    }
    return ans;
}


int main(){
	scanf("%d %d", &n, &m);//输入边数和点数 
	c = new arr[m * 2 + 5];// 要开两倍，因为要保存正反边
	r = new int[n + 5];
	d = new int[n + 5];
	tot = 1;// 这里初始化一定是1 
	edge = new int*[n + 5];
	for (int i = 0; i <= n; i ++){
		r[i] = 0;
		edge[i] = new int[n + 5];
		for (int j = 0; j <= n; j ++)
			edge[i][j] = 0;
	}
	for (int i = 0; i < 2 * m + 5; i ++)
		c[i].next = 0;
	int x, y, z;
	for (int i = 0; i < m; i ++){
		scanf("%d %d %d", &x, &y, &z);
		if (alg_mode == 1){
			add(x, y, z);
			add(y, x, z);//反向边 
		}else if(alg_mode == 2){
			edge[x - 1][y - 1] += z;
		}
		
	}
	if (alg_mode == 1){//dinic 
		int s = 1, t = n;//s源点。t汇点 
		int i;//增广的流量 
		int maxflow = 0;//最大流 
		while (bfs(s, t)){
			while (i = dinic(s, INF, t))
				maxflow += i;
		}
		printf("maxflow = %d\n", maxflow);
	}else{
		if (alg_mode == 2){//EK 
			printf("maxflow = %d\n", EK());
		}
	}
}
Download as text