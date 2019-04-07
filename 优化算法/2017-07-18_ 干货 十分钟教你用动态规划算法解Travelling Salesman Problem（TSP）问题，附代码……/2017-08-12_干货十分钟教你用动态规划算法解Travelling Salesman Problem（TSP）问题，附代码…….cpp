
#include<bits/stdc++.h>
using namespace std;
// 定义常量
const int INF = 0x3f3f3f3f;
#define sqr(x) ((x)*(x))
// 定义变量
string file_name;
int type; // type == 1 满秩矩阵格式, type == 2 二维坐标式
int s;
int N;// 城市结点数量
int init_point;
double **dp; // 动态规划状态数组dp[i][j]，i表示集合V’，j表示当前到达的城市结点
double **dis; // 两个城市结点之间的距离
double ans;
// 定义结构体
struct vertex{
  double x, y; // 城市结点的坐标
  int id; // 城市结点的id
  int input(FILE *fp){
    return fscanf(fp, "%d %lf %lf", &id, &x, &y);
  }
}*node;
 
double EUC_2D(const vertex &a, const vertex &b){
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
 
void io(){ // 数据读入
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
      dis[i][j] = EUC_2D(node[i], node[j]);// 计算城市之间的距离
    }
  }
  fclose(fp);
  return;
}

void init(){ // 数据初始化
  dp = new double*[(1 << N) + 5];
  for(int i = 0; i < (1 << N); i++){
    dp[i] = new double[N + 5];
    for(int j = 0; j < N; j++)
    dp[i][j] = INF; 
  } // 初始化，除了dp[1][0]，其余值都为INF
  ans = INF;
  return;
}
 
double slove(){
  int M = (1 << N); 
  // M就是第四部分所说的V’状态总数，1<<N表示2^N，总共有2^N种状态
  dp[1][0] = 0; 
  // 假设固定出发点为0，从0出发回到0的花费为0。TSP只要求是一个环路，所以出发点可以任选
  for (int i = 1; i < M; i ++){ 
  // 枚举V’的所有状态
    for (int j = 1; j < N; j ++){ 
    // 选择下一个加入集合的城市
      if (i & (1 << j)) continue; 
      // 城市已经存在于V’之中
      if (!(i & 1)) continue; 
      // 出发城市固定为0号城市
      for (int k = 0; k < N; k ++){ 
      // 在V’这个城市集合中尝试每一个结点，并求出最优解
        if (i & (1 << k)){ 
        // 确保k已经在集合之中并且是上一步转移过来的结点
           dp[(1 << j) | i][j] = min(dp[(1 << j) | i][j], dp[i][k] + dis[k][j]); // 转移方程
          } // 将j点加入到i集合中
      }
    }
  }
  for (int i = 0; i < N; i ++)
  ans = min(dp[M - 1][i] + dis[i][0], ans);
  // 因为固定了出发点，所以要加上到城市0的距离。另外要从所有的完成整个环路的集合V’中选择，完成最后的转移
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
