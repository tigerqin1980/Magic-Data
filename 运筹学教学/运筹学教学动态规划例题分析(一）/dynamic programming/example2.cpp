#include<bits/stdc++.h>
using namespace std;

int **dp; // dp[i][j] ��ʾ��һ��������i���ڶ���������j��ʱ�����С����
int m, n; // ��ʾ�������ӵ�������
int T; // T ΪĿ�꺯��ֵ 
struct arr{
	int x, y;
};

arr make_arr(int x, int y){
	arr tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

bool operator <(const arr &a, const arr &b){
	return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

bool operator ==(const arr &a, const arr &b){
	return (a.x == b.x && a.y == b.y);
}

map<arr, arr> solution;

void dfs(int x, int y){
	//�ﵽĿ��ֵ 
	if (x == T || y == T) return;
	
	//����B 
	if (dp[x][0] < 0){
		dp[x][0] = dp[x][y] + 1;
		dfs(x, 0);
		solution[make_arr(x, 0)] = make_arr(x, y);
	} 
	
	//����A 
	if (dp[m][y] < 0){
		dp[m][y] = dp[x][y] + 1;
		dfs(m, y);
		solution[make_arr(m, y)] = make_arr(x, y);
	}
	
	//����B
	if (dp[x][n] < 0){
		dp[x][n] = dp[x][y] + 1;
		dfs(x, n);
		solution[make_arr(x, n)] = make_arr(x, y);
	} 
	
	//����A
	if (dp[0][y] < 0) {
		dp[0][y] = dp[x][y] + 1;
		dfs(0, y);
		solution[make_arr(0, y)] = make_arr(x, y);
	}
	
	//A����B
	if (x + y <= n && dp[0][x + y] < 0){
		dp[0][x + y] = dp[x][y] + 1;
		dfs(0, x + y);
		solution[make_arr(0, x + y)] = make_arr(x, y);
	} 
	
	if (x + y > n && dp[x - n + y][n] < 0){
		dp[x - n + y][n] = dp[x][y] + 1;
		dfs(x - n + y, n);
		solution[make_arr(x - n + y, n)] = make_arr(x, y);
	}
	
	//B����A
	if (x + y <= m && dp[x + y][0] < 0){
		dp[x + y][0] = dp[x][y] + 1;
		dfs(x + y, 0);
		solution[make_arr(x + y, 0)] = make_arr(x, y);
	} 
	
	if (x + y > m && dp[m][x + y - m] < 0){
		dp[m][x + y - m] = dp[x][y] + 1;
		dfs(m, x + y - m);
		solution[make_arr(m, x + y - m)] = make_arr(x, y);//��¼·������ͬ 
	}
	
}


int main(){
	scanf("%d %d %d", &m, &n, &T);
	
	dp = new int*[m + 1];
	for (int i = 0; i <= m; i ++){
		dp[i] = new int[n + 1];
		for (int j = 0; j <= n; j ++){
			dp[i][j] = -1;
		}
	}
	dp[0][0] = 0;
	dfs(0, 0);
	int id_x, id_y;
	int ans = 0x7fffffff, ans1 = ans, ans2 = ans;
	if (T > m) {
		for (int i = 0; i <= m; i ++) 
			if (dp[i][T] > 0 && ans1 > dp[i][T] + (int)(i > 0)) {
				ans1 = dp[i][T] + (i > 0);
				id_x = i;
			}
	}
	else if (T > n){
		for (int i = 0; i <= n; i ++) 
			if (dp[T][i] > 0 && ans2 > dp[T][i] + (int)(i > 0)) {
				ans2 = dp[T][i] + (i > 0);
				id_y = i;
			}
	}
	else{
		for (int i = 0; i <= m; i ++) 
			if (dp[i][T] > 0 && ans1 > dp[i][T] + (int)(i > 0)) {
				ans1 = dp[i][T] + (i > 0);
				id_x = i;
			}
		for (int i = 0; i <= n; i ++) 
			if (dp[T][i] > 0 && ans2 > dp[T][i] + (int)(i > 0)) {
				ans2 = dp[T][i] + (i > 0);
				id_y = i;
			}
	}
	if (ans1 < ans2){
		ans = ans1 + 1;
		printf("%d %d\n", 0, T);
		arr tmp = make_arr(id_x, T);
		while (tmp.x || tmp.y){
			printf("%d %d\n", tmp.x, tmp.y);
			tmp = solution[tmp];
		} 
		printf("%d %d\n", tmp.x, tmp.y);
	}else{
		ans = ans2 + 1;
		printf("%d %d\n", T, 0);
		arr tmp = make_arr(T, id_y);
		while (tmp.x || tmp.y){
			printf("%d %d\n", tmp.x, tmp.y);
			tmp = solution[tmp];
		} 
		printf("%d %d\n", tmp.x, tmp.y);
	}
	printf("%d\n", ans);
}
