/*

	example input: 30 3
	example output: win
*/

#include<bits/stdc++.h>
using namespace std;
int n, k;// n�����ÿ��ȡ1..k�� 
int *dp;
int main(){
	scanf("%d %d", &n, &k);
	dp = new int[n + 1];
	for (int i = 1; i <= n; i ++) dp[i] = 0;
	
	dp[1] = 1;// ����һ������
	 
	for (int i = 1; i <= n; i += k + 1) dp[i] = 1;// ÿ��k+1������һ�α���̬ 
	
	if (dp[n]) printf("lose\n");
	else printf("win\n");
}
