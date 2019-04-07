/*
language: C++ 11
Author: Xing He
School: HuaZhong University of science and technology
compilier: g++.exe ACS.cpp -o ACS.exe -Ofast -std=c++11 

*/

#include<bits/stdc++.h>
using namespace std;
int type;// type == 1 全矩阵, type == 2 二维欧拉距离 
// const
const int INF = 0x3f3f3f3f;
#define sqr(x) ((x)*(x))
#define eps 1e-8
#define percent 0.99
#define MAX_ITERATION 1000
//variables
string file_name;
int N;//城市数量 
double **dis;//城市间距离 
int **TabuList;// 禁忌表
double **Delta;//邻域变化评价函数值 
bool *vis; // 标记是否被访问 
int TabuLength;
struct vertex{
	double x, y;// 城市坐标 
	int id;// 城市编号 
	
	int input(FILE *fp){
		return fscanf(fp, "%lf %lf",  &x, &y);
	}
	
}*node;


struct Path{
	int *path;//解结构 
	double L;//目标值 
	int n;//数据规模 
	void initlization(int x){
		path = new int[x];
		n = x;
		L = INF;
		return;
	}//初始化 
	
	double calc(){
		double ans = 0;
		for (int i = 0; i < n - 1; i ++)
			ans += dis[path[i]][path[i + 1]];
		L = ans + dis[path[n - 1]][path[0]];
		return ans;
	}//计算结果 
	
	double get_edge(int i, int j){
		if (i == n) i = 0;
		if (j == n) j = 0;
		if (i == -1) i = n - 1;
		if (j == -1) j = n - 1;
		return dis[path[i]][path[j]];
	}
	
	double swap_operator(int index_i, int index_j){
		if (index_i == index_j || (index_i == 0 && index_j == n) || (index_j == 0 && index_i == n)) return INF;
		double delta = 0;
 		if(index_i == index_j - 1 || index_i == index_j + n - 1){ 
        	delta += get_edge(index_i, index_j + 1) + get_edge(index_i - 1,index_j);
        	delta -= get_edge(index_i - 1, index_i) + get_edge(index_j, index_j + 1);
    	} 
       	else if(index_i == index_j + 1 || index_j == index_i + n -1){
           delta += get_edge(index_j, index_i + 1) + get_edge(index_j - 1,index_i);
           delta -= get_edge(index_j - 1, index_j) + get_edge(index_i,index_i + 1);
       	}
       	else{
           delta += get_edge(index_j, index_i - 1) + get_edge(index_j,index_i + 1);
           delta += get_edge(index_i, index_j - 1) + get_edge(index_i,index_j + 1);
           delta -= get_edge(index_i, index_i - 1) + get_edge(index_i,index_i + 1);
           delta -= get_edge(index_j, index_j - 1) + get_edge(index_j,index_j + 1);
      	}
       return delta;
	}//swap邻域计算 
	
	Path copy(Path s){
		n = s.n;
		L = s.L;
		this->path = new int[n];
		for (int i = 0; i < n; i ++)
			this->path[i] = s.path[i];
		return *this;
	}
	
	void print(FILE *fp){
		fprintf(fp, "Best_solution:%.0lf\n", L);
		for (int i = 0; i < n; i ++)
			fprintf(fp, "%d->", path[i] + 1);
		fprintf(fp, "%d\n", path[0] + 1);
		return;
	}//输出结果 
	
}solution, best;//当前解，最优解 

bool operator <(const Path &a, const Path &b){
		return a.L < b.L;
}

double EUC_2D(const vertex &a, const vertex &b){
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
} 

void io(){//输入
	printf("input file_name and data type\n");
	cin >> file_name >> type;
	FILE *fp = fopen(file_name.c_str(), "r");
	fscanf(fp, "%d", &N);
	node = new vertex[N + 5];
	dis = new double*[N + 5];
	double tmp = 0;
	int cnt = 0;
	if (type == 1){
		for (int i = 0; i < N; i ++){
			dis[i] = new double[N];
			for (int j = 0; j < N; j ++){
				fscanf(fp, "%lf", &dis[i][j]);
			}
		}
	}else{
		for (int i = 0; i < N; i ++)
			node[i].input(fp);		
		for (int i = 0; i < N; i ++){
			dis[i] = new double[N];
			for (int j = 0; j < N; j ++){
				dis[i][j] = EUC_2D(node[i], node[j]);// 计算距离		
			}
		}
	}
	fclose(fp);
	return;
}

int get_next(int x){
	double MIN = INF;
	int ans = 0;
	for (int i = 0; i < N; i ++){
		if (dis[x][i] < MIN && !vis[i]){
			MIN = dis[x][i];
			ans = i;
		}
	}
	return ans;
}//贪心选择下一个

void construction_init_solution(){
	int now = 0;
	vis[now] = 1;
	for (int i = 1; i < N; i ++){
		int s = get_next(now);
		solution.path[i] = s;
		now = s;
		vis[now] = 1;
	}
	solution.calc();
	best = solution;
	Delta = new double*[N];
	for (int i = 0; i < N; i ++){
		Delta[i] = new double[N];
		for (int j = 0; j < N; j ++){
			Delta[i][j] = solution.swap_operator(i, j);
		}
	}
	best.print(stdout);
}//贪心构造初始解 

void init(){
	solution.initlization(N);
	best.initlization(N);
	solution.path[0] = 0;
	TabuList = new int*[N];
	vis = new bool[N];
	TabuLength = (int)(N * percent);//设置禁忌步长 
	for (int i = 0; i < N; i ++){
		TabuList[i] = new int[N];
		vis[i] = 0;
		for (int j = 0; j < N; j ++){
			TabuList[i][j] = -TabuLength;
		}
	}//初始化禁忌表 
	
}
int r, s;
double neighbour(int round, Path sol){
	double delta = 0, MIN = INF;
	r = 0, s = 0;
	for (int i = 0; i < N; i ++)
		for (int j = 0; j < N; j ++){
			if (TabuList[i][j] + TabuLength > round && solution.L + Delta[i][j] >= best.L) continue;
			if (Delta[i][j] < MIN){
				MIN = Delta[i][j];
				r = i;
				s = j;
			}
		}
	if (MIN == INF) MIN = 0;
	return MIN;
}//邻域选择操作 

void update(int i){
	if (i == -1) i = N - 1;
	if (i == N) i = 0;
	for (int j = 0; j < N; j ++){
		if (i != j){
			Delta[i][j] = solution.swap_operator(i, j);
			Delta[j][i] = solution.swap_operator(j, i);
		}
			
	}
	return;
}// 更新Delta值 

void Delta_update(){
	int index_i = r, index_j = s;
	if(index_i == index_j - 1 || index_i == index_j + N - 1){ 
		update(index_i); update(index_j); 
		update(index_i - 1); update(index_j + 1);
	}else if(index_i == index_j + 1 || index_j == index_i + N - 1){
		update(index_i); update(index_j); 
		update(index_i + 1); update(index_j - 1);
	}else{
		update(index_i); update(index_j); 
		update(index_i + 1); update(index_j - 1);
		update(index_i - 1); update(index_j + 1);
	}
}// 更新有关的变化值，当r,s交换，只有与r,s相邻的城市在进行交换的时候会受到影响，避免重复计算 

void TabuSearch(){
	for (int round = 0; round < MAX_ITERATION; round ++){
		double delta = neighbour(round, solution);
		TabuList[r][s] = round;//更新禁忌表 
		//if (delta <= 0){
			swap(solution.path[r], solution.path[s]);
			Delta_update();
			solution.calc();	
		//}//更新当前解 
		if (solution < best) best.copy(solution) ;//更新最优解 
		printf("round:%d: best_so_far:%.0lf\n", round, best.L);
	}
}

int main(){
	srand((unsigned) time(0));//初始化随机种子 
	io();//输入 
	init();//初始化 
	construction_init_solution();//贪心构造初始解 
	TabuSearch();//禁忌搜索 
	best.print(stdout);//输出 
}
