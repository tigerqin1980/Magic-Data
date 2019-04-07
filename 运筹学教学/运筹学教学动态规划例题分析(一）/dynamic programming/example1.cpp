/*

	example input: 30 3
	example output: win
*/

#include<bits/stdc++.h>
using namespace std;
int n, k;// n个火柴，每次取1..k个 
int *dp;
int main(){
	scanf("%d %d", &n, &k);
	dp = new int[n + 1];
	for (int i = 1; i <= n; i ++) dp[i] = 0;
	
	dp[1] = 1;// 先手一根必输
	 
	for (int i = 1; i <= n; i += k + 1) dp[i] = 1;// 每隔k+1个出现一次必输态 
	
	if (dp[n]) printf("lose\n");
	else printf("win\n");
}
