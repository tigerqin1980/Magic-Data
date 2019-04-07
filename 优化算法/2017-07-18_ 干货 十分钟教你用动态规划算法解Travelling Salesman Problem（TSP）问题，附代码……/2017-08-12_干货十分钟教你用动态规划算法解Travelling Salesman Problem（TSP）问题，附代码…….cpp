
#include<bits/stdc++.h>
using namespace std;
// ���峣��
const int INF = 0x3f3f3f3f;
#define sqr(x) ((x)*(x))
// �������
string file_name;
int type; // type == 1 ���Ⱦ����ʽ, type == 2 ��ά����ʽ
int s;
int N;// ���н������
int init_point;
double **dp; // ��̬�滮״̬����dp[i][j]��i��ʾ����V����j��ʾ��ǰ����ĳ��н��
double **dis; // �������н��֮��ľ���
double ans;
// ����ṹ��
struct vertex{
  double x, y; // ���н�������
  int id; // ���н���id
  int input(FILE *fp){
    return fscanf(fp, "%d %lf %lf", &id, &x, &y);
  }
}*node;
 
double EUC_2D(const vertex &a, const vertex &b){
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
 
void io(){ // ���ݶ���
  printf("input file_name and data type\n");
  cin >> file_name >> type;
  FILE *fp = fopen(file_name.c_str(), "r");
  fscanf(fp, "%d", &N);
  node = new vertex[N + 5];
  dis = new double*[N + 5];
  if (type == 1){
    for (int i = 0; i < N; i ++){
      dis[i] = new double[N];
      for (int j = 0; j < N; j ++)
      fscanf(fp, "%lf", &dis[i][j]);
    }
  }
  else{
    for (int i = 0; i < N; i ++)
    node[i].input(fp);
    for (int i = 0; i < N; i ++){
      dis[i] = new double[N];
      for (int j = 0; j < N; j ++)
      dis[i][j] = EUC_2D(node[i], node[j]);// �������֮��ľ���
    }
  }
  fclose(fp);
  return;
}

void init(){ // ���ݳ�ʼ��
  dp = new double*[(1 << N) + 5];
  for(int i = 0; i < (1 << N); i++){
    dp[i] = new double[N + 5];
    for(int j = 0; j < N; j++)
    dp[i][j] = INF; 
  } // ��ʼ��������dp[1][0]������ֵ��ΪINF
  ans = INF;
  return;
}
 
double slove(){
  int M = (1 << N); 
  // M���ǵ��Ĳ�����˵��V��״̬������1<<N��ʾ2^N���ܹ���2^N��״̬
  dp[1][0] = 0; 
  // ����̶�������Ϊ0����0�����ص�0�Ļ���Ϊ0��TSPֻҪ����һ����·�����Գ����������ѡ
  for (int i = 1; i < M; i ++){ 
  // ö��V��������״̬
    for (int j = 1; j < N; j ++){ 
    // ѡ����һ�����뼯�ϵĳ���
      if (i & (1 << j)) continue; 
      // �����Ѿ�������V��֮��
      if (!(i & 1)) continue; 
      // �������й̶�Ϊ0�ų���
      for (int k = 0; k < N; k ++){ 
      // ��V��������м����г���ÿһ����㣬��������Ž�
        if (i & (1 << k)){ 
        // ȷ��k�Ѿ��ڼ���֮�в�������һ��ת�ƹ����Ľ��
           dp[(1 << j) | i][j] = min(dp[(1 << j) | i][j], dp[i][k] + dis[k][j]); // ת�Ʒ���
          } // ��j����뵽i������
      }
    }
  }
  for (int i = 0; i < N; i ++)
  ans = min(dp[M - 1][i] + dis[i][0], ans);
  // ��Ϊ�̶��˳����㣬����Ҫ���ϵ�����0�ľ��롣����Ҫ�����е����������·�ļ���V����ѡ���������ת��
  return ans;
}
 
int main(){
  io();
  init();
  string tmp = file_name + ".sol";
  FILE *fp = fopen(tmp.c_str(), "w");
  fprintf(fp, "%.2lf\n", slove());
  delete[] dp;
  delete[] node;
  delete[] dis;
  fclose(fp);
  return 0;
}
