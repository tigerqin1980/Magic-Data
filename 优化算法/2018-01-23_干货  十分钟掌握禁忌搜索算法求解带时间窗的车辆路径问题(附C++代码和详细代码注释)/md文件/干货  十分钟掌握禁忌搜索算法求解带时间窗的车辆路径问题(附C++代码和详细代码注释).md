
![](https://i.imgur.com/A8iuHH8.png)



#一    

##什么是禁忌搜索算法？

禁忌搜索算法（Tabu Search Algorithm，简称TS）起源于对于人类记忆功能的模仿，是一种亚启发式算法(meta-heuristics)。它从一个初始可行解(initial feasible solution)出发，试探一系列的特定搜索方向(移动)，选择让特定的目标函数值提升最多的移动。为了避免陷入局部最优解，禁忌搜索对已经历过的搜索过程信息进行记录，从而指导下一步的搜索方向。
禁忌搜索是人工智能的一种体现，是局部搜索的一种扩展。禁忌搜索是在邻域搜索(local search)的基础上，通过设置禁忌表（tabu list）来禁忌一些曾经执行过的操作，并利用藐视准则来解禁一些优秀的解。



#二

##禁忌搜索算法基本步骤：

###①  初始化
利用贪婪算法等局部搜索算法生成一个初始解，清空禁忌表，设置禁忌长度。
###②  邻域搜索产生候选解
根据步骤①产生初始解，通过搜索算子（search operators），如relocation、exchange、2-opt等，产生候选解(candidate solution)，并计算各个候选解的适应值（即解对应的目标函数值）。
###③  选择最好的候选解
从步骤②产生的所有候选解中选出适应值最好的候选解，将其与当前最好解(即搜索算法开始到现在找到的最好解)进行比较，如果优于当前最好解，那么就不考虑其是否被禁忌，用这个最好的候选解来更新当前最好解，并且作为下一个迭代的当前解，然后将对应的操作加入禁忌表；如果不优于当前最好解，就从所有候选解中选出不在禁忌状态下的最好解作为新的当前解，然后将对应操作加入禁忌表。
###④  判断终止条件
若满足终止条件，则立即停止并输出当前最好解；否则继续搜索。一般终止条件为是否到达一定的迭代次数或者达到了一个时间限制。

禁忌搜索算法流程图：

![](https://i.imgur.com/YzO9BEH.jpg)






禁忌搜索算法涉及编码解码（Encoding and decoding）、搜索算子（search operators）、邻域 （Neighborhood）、禁忌表（Tabu list）、禁忌长度（Tabu tenure）、候选解（Candidate solution）、藐视准则（Aspiration criterion）等关键组成部分。
关于禁忌搜索的上述相关内容在之前的推文中已有详细的介绍，分别从禁忌搜索的发展由来、主要构成要素和详细的实验结论三个角度给大家一一做了讲解，使大家对禁忌搜索有全方位的理解。下面给出两篇禁忌搜索推文的链接：干货 | 到底是什么算法，能让人们如此绝望？、干货|十分钟快速复习禁忌搜索(c++版)

下面我们以TSP问题为例说明介绍这些组成部分：如下图所示，有5个城市，任何两个城市之间的距离都是确定的，现要求一个旅行商从某城市出发必须经过每个城市一次且仅有一次，最后回到出发的城市，问如何确定一条最短的线路(每条边的长度已在图中标出)？


![](https://i.imgur.com/BaEF0fc.jpg)



##1.编码和解码（Encodingand Decoding）: 相关内容在之前的推文中出现，给出链接：干货 | 嘿！你和遗传算法的距离也许只差这一文(附C++代码和详细代码注释)，构造初始解如下图所示：


![](https://i.imgur.com/uh9xrlF.jpg)


初始解对应的适应值为

![](https://i.imgur.com/wZhKAvI.png)


##2.搜索算子：
  （1）Relocation算子
   该算子在当前解中选择并移除一个节点(node)，然后再选择一个位置将选中的节点插入。
例子：
   ![](https://i.imgur.com/LAZwa7u.jpg)



   如图所示，当前解中选择节点2，再选择插入位置节点3（之后），执行后得到候选解，此时适应值变化量为


![](https://i.imgur.com/XOT64KO.png)

  （2）Swap算子
   该算子在当前解中同时选择两个不同的节点，然后对这两个节点的位置交换。
   例子：

![](https://i.imgur.com/9EDvnCw.jpg)


   如图所示，当前解中选择节点2和4，再对这两个节点交换位置，执行后得到候选解2，此时适应值变化量为


##3.邻域 （Neighborhood）：从当前解对一系列的搜索方向进行一次试探（通过算子搜索一次）能得到的所有解的集合，即仅经过一次操作能得到的所有解。
  例子：
![](https://i.imgur.com/2aQG8L9.jpg)



如上图所示，通过②中搜索算子搜索一次得到的候选解的集合即为当前邻域。

##4.禁忌表（Tabu List）：记录当前所选择操作的状态变化，一般包括禁忌对象和禁忌长度。
  例子：

![](https://i.imgur.com/Q0SdwRz.jpg)

在初始解的邻域中，候选解10为所有候选解中改进最大的解（即|ΔF|最大，ΔF=-2）。因此，候选解10被选中作为下一个迭代的当前解，则禁忌对象如上图所示，l为禁忌长度（即在未来的l次迭代中禁止移动节点4）。

5.禁忌长度（Tabu Tenure）：禁止在之后的l次迭代中对禁忌表中所记录的状态进行改变，这里的l即称为禁忌长度。

6.候选解（Candidate Solution）：当前邻域中的解。

7.藐视准则（Aspiration Criterion）：从候选解集合中挑选出最好的候选解，将其与当前最好解进行比较，若其是被禁止的解但是优于当前最好解，那么就将其解禁，用来作为下一迭代的当前解并及替代当前最好解。藐视准则（Aspiration criterion）防止了因为禁忌表的存在，而错过优异解的情况出现。



三

禁忌搜索算法解带时间窗的车辆路径问题（VRPTW）

VRPTW问题可描述为：假设一个配送中心为周围若干个位于不同地理位置、且对货物送达时间有不相同要求的客户点提供配送服务。其中，配送中心全部用于运行的车辆都是同一型号的（即拥有相同的容量）；配送中心对车辆出入的时间有限制；车辆在所有客户点有相同的停留服务时间。
给出的连通G=(N,A)中，n+1个位置节点表示为集合N={0,1,2,...,n}，连接节点之间的边表示为集合A={(i,j):i≠j∈N}。其中节点0是仓库，剩余每个节点对应一个客户。假设车辆的速度恒定（即从节点i到节点j的行驶时间tij在数值上与其欧式距离dij相等）。可用的车辆数表示为m，所有车必须从位置0开始并回到位置0。每个点节i属于N且带有时间窗[a_i, b_i]，其中a_i和b_i分别表示节点i最早和最晚允许开始接受货物的时间。若节点i被选中且在路线r中，则决策变量y_{ri}的值为1，否则为0。若边(i,j)被选中且在路线r中，则决策变量x_{rij}的值为1，否则为0。路线r中车辆抵达客户i的时间点用决策变量s_{ri}表示。在车辆早抵达的情况下，车辆必须等候至时间窗起始时间点。若抵达时间点没有超出时间窗的结束时间点，则服务成功（即获得利润）。
VRPTW问题在之前的推文中有更详细的介绍，分别从VRPTW问题的由来、建模实例和CPLEX求解方法三个角度给大家有层次地剖析，使大家能对于VRPTW问题有更深入的了解。下面给出VRPTW问题推文的链接：干货|十分钟快速掌握CPLEX求解VRPTW数学模型（附JAVA代码及CPLEX安装流程）

本文参照文献编写代码，具体操作设置如下：
编码方式采取自然数编码，利用将车辆所需服务客户点的集合（解集）作为集合内元素数目大小的自然数数组。数组中各个元素的值代表各个客户点的编号，元素的顺序代表服务客户点的顺序。
搜索算子采用插入算子：删除原路径中的客户节点，遍历插入到任意车辆路径的任意位置，选取邻域最好解或者非禁忌最好解作为下一迭代的当前解。邻域为插入算子完全遍历能得到的解的集合。
总迭代次数和禁忌长度分别设置为2000和40。



四 

##代码说明

###(a). 代码模块说明

   代码一共分为main()、ReadIn_and_Initialization()、Construction()、Calculation()、Tabu_Search()、Check()和Output()等7个函数模块构成，其中main()函数构建了算法的主体框架；ReadIn_and_Initialization()函数的功能是初始化所有变量，完成数据读入操作并存储；Construction()、Calculation()、Tabu_Search()这3个函数则为整个禁忌搜索算法（构建初始解、计算对应解的适应值、对邻域进行搜索并选择对应操作进行禁忌）的实现过程；Check()函数的功能是用来检验解是否满足对应的所有约束；Output()函数输出结果。

###(b). 文本数据输入格式说明：

    采取读取文本格式来作为数据输入的形式，具体格式见下表：

![](https://i.imgur.com/LykIGuo.png)

   由上表可知，输入数据为一行七列的形式，依次为对应点的序号、横坐标、纵坐标、所需服务量、服务时间窗起始时间点、服务时间窗结束时间点和服务所需时间。由此可见，节点1为仓库（depot）,其他节点为待服务点。

```
Input
输入算例：（R101.txt）

    1      35.00      35.00       0.00       0.00     230.00       0.00
    2      41.00      49.00      10.00     161.00     171.00      10.00
    3      35.00      17.00       7.00      50.00      60.00      10.00
    4      55.00      45.00      13.00     116.00     126.00      10.00
    5      55.00      20.00      19.00     149.00     159.00      10.00
    6      15.00      30.00      26.00      34.00      44.00      10.00
    7      25.00      30.00       3.00      99.00     109.00      10.00
    8      20.00      50.00       5.00      81.00      91.00      10.00
    9      10.00      43.00       9.00      95.00     105.00      10.00
   10      55.00      60.00      16.00      97.00     107.00      10.00
   11      30.00      60.00      16.00     124.00     134.00      10.00
   12      20.00      65.00      12.00      67.00      77.00      10.00
   13      50.00      35.00      19.00      63.00      73.00      10.00
   14      30.00      25.00      23.00     159.00     169.00      10.00
   15      15.00      10.00      20.00      32.00      42.00      10.00
   16      30.00       5.00       8.00      61.00      71.00      10.00
   17      10.00      20.00      19.00      75.00      85.00      10.00
   18       5.00      30.00       2.00     157.00     167.00      10.00
   19      20.00      40.00      12.00      87.00      97.00      10.00
   20      15.00      60.00      17.00      76.00      86.00      10.00
   21      45.00      65.00       9.00     126.00     136.00      10.00
   22      45.00      20.00      11.00      62.00      72.00      10.00
   23      45.00      10.00      18.00      97.00     107.00      10.00
   24      55.00       5.00      29.00      68.00      78.00      10.00
   25      65.00      35.00       3.00     153.00     163.00      10.00
   26      65.00      20.00       6.00     172.00     182.00      10.00
   27      45.00      30.00      17.00     132.00     142.00      10.00
   28      35.00      40.00      16.00      37.00      47.00      10.00
   29      41.00      37.00      16.00      39.00      49.00      10.00
   30      64.00      42.00       9.00      63.00      73.00      10.00
   31      40.00      60.00      21.00      71.00      81.00      10.00
   32      31.00      52.00      27.00      50.00      60.00      10.00
   33      35.00      69.00      23.00     141.00     151.00      10.00
   34      53.00      52.00      11.00      37.00      47.00      10.00
   35      65.00      55.00      14.00     117.00     127.00      10.00
   36      63.00      65.00       8.00     143.00     153.00      10.00
   37       2.00      60.00       5.00      41.00      51.00      10.00
   38      20.00      20.00       8.00     134.00     144.00      10.00
   39       5.00       5.00      16.00      83.00      93.00      10.00
   40      60.00      12.00      31.00      44.00      54.00      10.00
   41      40.00      25.00       9.00      85.00      95.00      10.00
   42      42.00       7.00       5.00      97.00     107.00      10.00
   43      24.00      12.00       5.00      31.00      41.00      10.00
   44      23.00       3.00       7.00     132.00     142.00      10.00
   45      11.00      14.00      18.00      69.00      79.00      10.00
   46       6.00      38.00      16.00      32.00      42.00      10.00
   47       2.00      48.00       1.00     117.00     127.00      10.00
   48       8.00      56.00      27.00      51.00      61.00      10.00
   49      13.00      52.00      36.00     165.00     175.00      10.00
   50       6.00      68.00      30.00     108.00     118.00      10.00
   51      47.00      47.00      13.00     124.00     134.00      10.00
   52      49.00      58.00      10.00      88.00      98.00      10.00
   53      27.00      43.00       9.00      52.00      62.00      10.00
   54      37.00      31.00      14.00      95.00     105.00      10.00
   55      57.00      29.00      18.00     140.00     150.00      10.00
   56      63.00      23.00       2.00     136.00     146.00      10.00
   57      53.00      12.00       6.00     130.00     140.00      10.00
   58      32.00      12.00       7.00     101.00     111.00      10.00
   59      36.00      26.00      18.00     200.00     210.00      10.00
   60      21.00      24.00      28.00      18.00      28.00      10.00
   61      17.00      34.00       3.00     162.00     172.00      10.00
   62      12.00      24.00      13.00      76.00      86.00      10.00
   63      24.00      58.00      19.00      58.00      68.00      10.00
   64      27.00      69.00      10.00      34.00      44.00      10.00
   65      15.00      77.00       9.00      73.00      83.00      10.00
   66      62.00      77.00      20.00      51.00      61.00      10.00
   67      49.00      73.00      25.00     127.00     137.00      10.00
   68      67.00       5.00      25.00      83.00      93.00      10.00
   69      56.00      39.00      36.00     142.00     152.00      10.00
   70      37.00      47.00       6.00      50.00      60.00      10.00
   71      37.00      56.00       5.00     182.00     192.00      10.00
   72      57.00      68.00      15.00      77.00      87.00      10.00
   73      47.00      16.00      25.00      35.00      45.00      10.00
   74      44.00      17.00       9.00      78.00      88.00      10.00
   75      46.00      13.00       8.00     149.00     159.00      10.00
   76      49.00      11.00      18.00      69.00      79.00      10.00
   77      49.00      42.00      13.00      73.00      83.00      10.00
   78      53.00      43.00      14.00     179.00     189.00      10.00
   79      61.00      52.00       3.00      96.00     106.00      10.00
   80      57.00      48.00      23.00      92.00     102.00      10.00
   81      56.00      37.00       6.00     182.00     192.00      10.00
   82      55.00      54.00      26.00      94.00     104.00      10.00
   83      15.00      47.00      16.00      55.00      65.00      10.00
   84      14.00      37.00      11.00      44.00      54.00      10.00
   85      11.00      31.00       7.00     101.00     111.00      10.00
   86      16.00      22.00      41.00      91.00     101.00      10.00
   87       4.00      18.00      35.00      94.00     104.00      10.00
   88      28.00      18.00      26.00      93.00     103.00      10.00
   89      26.00      52.00       9.00      74.00      84.00      10.00
   90      26.00      35.00      15.00     176.00     186.00      10.00
   91      31.00      67.00       3.00      95.00     105.00      10.00
   92      15.00      19.00       1.00     160.00     170.00      10.00
   93      22.00      22.00       2.00      18.00      28.00      10.00
   94      18.00      24.00      22.00     188.00     198.00      10.00
   95      26.00      27.00      27.00     100.00     110.00      10.00
   96      25.00      24.00      20.00      39.00      49.00      10.00
   97      22.00      27.00      11.00     135.00     145.00      10.00
   98      25.00      21.00      12.00     133.00     143.00      10.00
   99      19.00      21.00      10.00      58.00      68.00      10.00
  100      20.00      26.00       9.00      83.00      93.00      10.00
  101      18.00      18.00      17.00     185.00     195.00      10.00

//*****************************************************************
//禁忌搜索算法求解带时间窗的车辆路径问题(VRPTW_TS)
//*****************************************************************
//Reference
//J-F Cordeau, Laporte, G., & Mercier, A. (2001). A Unified Tabu Search Heuristic for Vehicle Routing Problems with Time Windows. The Journal of the Operational Research Society, 52(8), 928-936. Retrieved from http://www.jstor.org/stable/822953
//Solomon, M. (1987). Algorithms for the Vehicle Routing and Scheduling Problems with Time Window Constraints. Operations Research, 35(2), 254-265. Retrieved from http://www.jstor.org/stable/170697
//*****************************************************************
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

#define cin fin
#define cout fout
#define INF 0x3ffffff
#define Customer_Number 100   //算例中除仓库以外的顾客节点个数
#define Capacity 200   //车辆的容量
#define Iter_Max 2000   //搜索最大迭代次数
#define Tabu_tenure 20   //禁忌时长

ifstream fin("R101.txt");
ofstream fout("R101_Output.txt");

struct Customer_Type {
    int Number;   //节点自身编号
    int R;   //节点所属车辆路径编号
    double X, Y;   //节点横纵坐标
    double Begin, End, Service;   //节点被访问的最早时间，最晚时间以及服务时长
    double Demand;   //节点的需求量
} Customer[Customer_Number + 10];   //仓库节点编号为1，顾客节点编号为2-101

struct Route_Type {
    double Load;   //单条路径装载量
    double SubT;   //单条路径违反各节点时间窗约束时长总和
    double Dis;   //单条路径总长度
    vector<Customer_Type> V;   //单条路径上顾客节点序列
} Route[Customer_Number + 10], Route_Ans[Customer_Number + 10];   //车辆路径及搜索到最优的车辆路径

int Vehicle_Number = Customer_Number;   //由于无车辆数量限制，因此将上限设为顾客总数
int Tabu[Customer_Number + 10][Customer_Number + 10];   //禁忌表用于禁忌节点插入操作
int TabuCreate[Customer_Number + 10];   //禁忌表用于禁忌拓展新路径或使用新车辆

double Ans;
double Alpha = 1, Beta = 1, Sita = 0.5;
double Graph[Customer_Number + 10][Customer_Number + 10];
//************************************************************
double Distance ( Customer_Type C1, Customer_Type C2 ) {   //计算图上各节点间的距离
    return sqrt ( ( C1.X - C2.X ) * ( C1.X - C2.X ) + ( C1.Y - C2.Y ) * ( C1.Y - C2.Y ) );
}
//************************************************************
double Calculation ( Route_Type R[], int Cus, int NewR ) {   //计算路径规划R的目标函数值
    //目标函数主要由三个部分组成：D路径总长度（优化目标），Q超出容量约束总量，T超出时间窗约束总量
    //目标函数结构为 f(R) = D + Alpha * Q + Beta * T, 第一项为问题最小化目标，后两项为惩罚部分
    //其中Alpha与Beta为可变参数，分别根据当前解是否满足两个约束来进行变化（在Check函数中更新，由于Check针对每轮迭代得到的解）
    double Q = 0;
    double T = 0;
    double D = 0;


    //计算单条路径超出容量约束的总量
    for ( int i = 1; i <= Vehicle_Number; ++i )
        if ( R[i].V.size() > 2 && R[i].Load > Capacity )
            Q = Q + R[i].Load - Capacity;

    //计算单条路径上各个节点超出时间窗约束的总量（仅更新进行移除和插入节点操作的两条路径）
    double ArriveTime = 0;
    R[Customer[Cus].R].SubT = 0;
    for ( int j = 1; j < R[Customer[Cus].R].V.size(); ++j ) {
        ArriveTime = ArriveTime + R[Customer[Cus].R].V[j - 1].Service + Graph[R[Customer[Cus].R].V[j - 1].Number][R[Customer[Cus].R].V[j].Number];
        if ( ArriveTime > R[Customer[Cus].R].V[j].End )
            R[Customer[Cus].R].SubT = R[Customer[Cus].R].SubT + ArriveTime - R[Customer[Cus].R].V[j].End;
        else if ( ArriveTime < R[Customer[Cus].R].V[j].Begin )
            ArriveTime = R[Customer[Cus].R].V[j].Begin;
    }

    ArriveTime = 0;
    R[NewR].SubT = 0;
    for ( int j = 1; j < R[NewR].V.size(); ++j ) {
        ArriveTime = ArriveTime + R[NewR].V[j - 1].Service + Graph[R[NewR].V[j - 1].Number][R[NewR].V[j].Number];
        if ( ArriveTime > R[NewR].V[j].End )
            R[NewR].SubT = R[NewR].SubT + ArriveTime - R[NewR].V[j].End;
        else if ( ArriveTime < R[NewR].V[j].Begin )
            ArriveTime = R[NewR].V[j].Begin;
    }

    for ( int i = 1; i <= Vehicle_Number; ++i )
        T += R[i].SubT;


    //计算路径总长度
    for ( int i = 1; i <= Vehicle_Number; ++i )
        D += R[i].Dis;

    return D + Alpha * Q + Beta * T;
}
//************************************************************
bool Check ( Route_Type R[] ) {   //检验路径规划R是否满足所有约束
    double Q = 0;
    double T = 0;
    double D = 0;

    //检查是否满足容量约束
    for ( int i = 1; i <= Vehicle_Number; ++i )
        if ( R[i].V.size() > 2 && R[i].Load > Capacity )
            Q = Q + R[i].Load - Capacity;

    //检查是否满足时间窗约束
    for ( int i = 1; i <= Vehicle_Number; ++i )
        T += R[i].SubT;

    //分别根据约束满足的情况更新Alpha和Beta值
    if ( Q == 0 && Alpha >= 0.001 )
        Alpha /= ( 1 + Sita );
    else if ( Q != 0 && Alpha <= 2000 )
        Alpha *= ( 1 + Sita );

    if ( T == 0 && Beta >= 0.001 )
        Beta /= ( 1 + Sita );
    else if ( T != 0 && Beta <= 2000 )
        Beta *= ( 1 + Sita );

    if ( T == 0 && Q == 0 )
        return true;
    else
        return false;
}
//************************************************************
void Copy_Route() {   //将路径规划Route的内容复制给路径规划Route_Ans
    for ( int i = 1; i <= Vehicle_Number; ++i ) {
        Route_Ans[i].Load = Route[i].Load;
        Route_Ans[i].V.clear();
        for ( int j = 0; j < Route[i].V.size(); ++j )
            Route_Ans[i].V.push_back ( Route[i].V[j] );
    }
}
//************************************************************
void Output ( Route_Type R[] ) {//结果输出
    cout << "************************************************************" << endl;
    cout << "The Minimum Total Distance = " << Ans << endl;
    cout << "Concrete Schedule of Each Route as Following : " << endl;
    int M = 0;
    for ( int i = 1; i <= Vehicle_Number; ++i )
        if ( R[i].V.size() > 2 ) {
            M++;
            cout << "No." << M << " : ";
            for ( int j = 0; j < R[i].V.size() - 1; ++j )
                cout << R[i].V[j].Number << " -> ";
            cout << R[i].V[R[i].V.size() - 1].Number << endl;
        }

    //检验距离计算是否正确
    double Check_Ans = 0;
    for ( int i = 1; i <= Vehicle_Number; ++i )
        for ( int j = 1; j < R[i].V.size(); ++j )
            Check_Ans += Graph[R[i].V[j - 1].Number][R[i].V[j].Number];

    cout << "Check_Ans = " << Check_Ans << endl;
    cout << "************************************************************" << endl;
}
//************************************************************
void ReadIn_and_Initialization() {//数据读入及初始化
    for ( int i = 1; i <= Customer_Number + 1; ++i )
        cin >> Customer[i].Number >> Customer[i].X >> Customer[i].Y >> Customer[i].Demand
            >> Customer[i].Begin >> Customer[i].End >> Customer[i].Service;

    //初始化每条路径，默认路径收尾为仓库，且首仓库最早最晚时间均为原仓库最早时间，尾仓库则均为原仓库最晚时间
    Customer[1].R = -1;
    for ( int i = 1; i <= Vehicle_Number; ++i ) {
        if ( !Route[i].V.empty() )
            Route[i].V.clear();
        Route[i].V.push_back ( Customer[1] );
        Route[i].V.push_back ( Customer[1] );
        Route[i].V[0].End = Route[i].V[0].Begin;
        Route[i].V[1].Begin = Route[i].V[1].End;
        Route[i].Load = 0;
    }

    Ans = INF;

    for ( int i = 1; i <= Customer_Number + 1; ++i )
        for ( int j = 1; j <= Customer_Number + 1; ++j )
            Graph[i][j] = Distance ( Customer[i], Customer[j] );
}
//************************************************************
void Construction() {   //构造初始路径
    int Customer_Set[Customer_Number + 10];
    for ( int i = 1; i <= Customer_Number; ++i )
        Customer_Set[i] = i + 1;

    int Sizeof_Customer_Set = Customer_Number;
    int Current_Route = 1;

    //以满足容量约束为目的的随机初始化
    //即随机挑选一个节点插入到第m条路径中，若超过容量约束，则插入第m+1条路径
    //且插入路径的位置由该路径上已存在的各节点最早时间的升序决定
    while ( Sizeof_Customer_Set > 0 ) {
		int K = rand() % Sizeof_Customer_Set + 1;
		int C = Customer_Set[K];
		Customer_Set[K] = Customer_Set[Sizeof_Customer_Set];
		Sizeof_Customer_Set--;

        /*int K = rand() % Sizeof_Customer_Set + 1;
        int C = Customer_Set[K];
        Customer_Set[K] = Customer_Set[Sizeof_Customer_Set];
        Sizeof_Customer_Set--;*/
		//将当前服务过的节点赋值为最末节点值,数组容量减1

        if ( Route[Current_Route].Load + Customer[C].Demand > Capacity )
            Current_Route++;

        for ( int i = 0; i < Route[Current_Route].V.size() - 1; i++ )
            if ( ( Route[Current_Route].V[i].Begin <= Customer[C].Begin ) && ( Customer[C].Begin <= Route[Current_Route].V[i + 1].Begin ) ) {
                Route[Current_Route].V.insert ( Route[Current_Route].V.begin() + i + 1, Customer[C] );
                Route[Current_Route].Load += Customer[C].Demand;
                Customer[C].R = Current_Route;
                break;
            }
    }

    //初始化计算超过容量约束的总量和超过时间窗约束的总量
    for ( int i = 1; i <= Vehicle_Number; ++i ) {
        double ArriveTime = Route[i].V[0].Begin;
        Route[i].SubT = 0;
        Route[i].Dis = 0;
        for ( int j = 1; j < Route[i].V.size(); ++j ) {
            ArriveTime = ArriveTime + Route[i].V[j - 1].Service + Graph[Route[i].V[j - 1].Number][Route[i].V[j].Number];
            Route[i].Dis += Graph[Route[i].V[j - 1].Number][Route[i].V[j].Number];
            if ( ArriveTime > Route[i].V[j].End )
                Route[i].SubT = Route[i].SubT + ArriveTime - Route[i].V[j].End;
            else if ( ArriveTime < Route[i].V[j].Begin )
                ArriveTime = Route[i].V[j].Begin;
        }
    }
}
//************************************************************
void Tabu_Search() {   //禁忌搜索
    //禁忌搜索采取插入算子，即从一条路径中选择一点插入到另一条路径中
    //在该操作下形成的邻域中选取使目标函数最小的非禁忌解或者因满足藐视法则而被解禁的解
    double Temp1;
    double Temp2;

    for ( int i = 2; i <= Customer_Number + 1; ++i ) {
        for ( int j = 1; j <= Vehicle_Number; ++j )
            Tabu[i][j] = 0;
        TabuCreate[i] = 0;
    }

    int Iteration = 0;
    while ( Iteration < Iter_Max ) {
        Iteration++;
        int BestC = 0, BestR = 0, BestP = 0, P;
        double BestV = INF;


        for ( int i = 2; i <= Customer_Number + 1; ++i ) {
            for ( int j = 1; j < Route[Customer[i].R].V.size(); ++j )
                if ( Route[Customer[i].R].V[j].Number == i ) {
                    P = j;
                    break;
                }
            //从节点原路径中去除该节点的需求
            Route[Customer[i].R].Load -= Customer[i].Demand;
            //从节点原路径中去除该节点所组成的路径并重组
            Route[Customer[i].R].Dis = Route[Customer[i].R].Dis - Graph[Route[Customer[i].R].V[P - 1].Number][Route[Customer[i].R].V[P].Number]
                                       - Graph[Route[Customer[i].R].V[P].Number][Route[Customer[i].R].V[P + 1].Number] + Graph[Route[Customer[i].R].V[P - 1].Number][Route[Customer[i].R].V[P + 1].Number];
            //从节点原路径中去除节点
            Route[Customer[i].R].V.erase ( Route[Customer[i].R].V.begin() + P );

            for ( int j = 1; j <= Vehicle_Number; ++j )
                //禁忌插入操作，后者为禁止使用新的车辆
                if ( ( Route[j].V.size() > 2 && Tabu[i][j] <= Iteration ) || ( Route[j].V.size() == 2 && TabuCreate[i] <= Iteration ) ) {
                    for ( int l = 1; l < Route[j].V.size(); ++l )
                        if ( Customer[i].R != j ) {
                            //在节点新路径中加上该节点的需求
                            Route[j].Load += Customer[i].Demand;
                            //在节点新路径中加上该节点插入后所组成的路径并断开原路径
                            Route[j].Dis = Route[j].Dis - Graph[Route[j].V[l - 1].Number][Route[j].V[l].Number]
                                           + Graph[Route[j].V[l - 1].Number][Customer[i].Number] + Graph[Route[j].V[l].Number][Customer[i].Number];
                            //在节点新路径中插入节点
                            Route[j].V.insert ( Route[j].V.begin() + l, Customer[i] );
                            Temp1 = Route[Customer[i].R].SubT;
                            Temp2 = Route[j].SubT;

                            double TempV = Calculation ( Route, i, j );
                            if ( TempV < BestV ) {
                                BestV = TempV;
                                BestC = i, BestR = j, BestP = l;
                            }
                            //节点新路径复原
                            Route[Customer[i].R].SubT = Temp1;
                            Route[j].SubT = Temp2;
                            Route[j].V.erase ( Route[j].V.begin() + l );
                            Route[j].Load -= Customer[i].Demand;
                            Route[j].Dis = Route[j].Dis + Graph[Route[j].V[l - 1].Number][Route[j].V[l].Number]
                                           - Graph[Route[j].V[l - 1].Number][Customer[i].Number] - Graph[Route[j].V[l].Number][Customer[i].Number];
                        }
                }
            //节点原路径复原
            Route[Customer[i].R].V.insert ( Route[Customer[i].R].V.begin() + P, Customer[i] );
            Route[Customer[i].R].Load += Customer[i].Demand;
            Route[Customer[i].R].Dis = Route[Customer[i].R].Dis + Graph[Route[Customer[i].R].V[P - 1].Number][Route[Customer[i].R].V[P].Number]
                                       + Graph[Route[Customer[i].R].V[P].Number][Route[Customer[i].R].V[P + 1].Number] - Graph[Route[Customer[i].R].V[P - 1].Number][Route[Customer[i].R].V[P + 1].Number];
        }

        if ( Route[BestR].V.size() == 2 )
            TabuCreate[BestC] = Iteration + 2 * Tabu_tenure + rand() % 10;
        Tabu[BestC][Customer[BestC].R] = Iteration + Tabu_tenure + rand() % 10;
        for ( int i = 1; i < Route[Customer[BestC].R].V.size(); ++i )
            if ( Route[Customer[BestC].R].V[i].Number == BestC ) {
                P = i;
                break;
            }

        //依据上述循环中挑选的结果，生成新的总体路径规划
        //更新改变过的各单条路径的载重，距离长度，超出时间窗的总量
        Route[Customer[BestC].R].Load -= Customer[BestC].Demand;
        Route[Customer[BestC].R].Dis = Route[Customer[BestC].R].Dis - Graph[Route[Customer[BestC].R].V[P - 1].Number][Route[Customer[BestC].R].V[P].Number]
                                       - Graph[Route[Customer[BestC].R].V[P].Number][Route[Customer[BestC].R].V[P + 1].Number] + Graph[Route[Customer[BestC].R].V[P - 1].Number][Route[Customer[BestC].R].V[P + 1].Number];

        Route[Customer[BestC].R].V.erase ( Route[Customer[BestC].R].V.begin() + P );
        Route[BestR].Dis = Route[BestR].Dis - Graph[Route[BestR].V[BestP - 1].Number][Route[BestR].V[BestP].Number]
                           + Graph[Route[BestR].V[BestP - 1].Number][Customer[BestC].Number] + Graph[Route[BestR].V[BestP].Number][Customer[BestC].Number];
        Route[BestR].Load += Customer[BestC].Demand;
        Route[BestR].V.insert ( Route[BestR].V.begin() + BestP, Customer[BestC] );

        double ArriveTime = 0;
        Route[BestR].SubT = 0;
        for ( int j = 1; j < Route[BestR].V.size(); ++j ) {
            ArriveTime = ArriveTime + Route[BestR].V[j - 1].Service + Graph[Route[BestR].V[j - 1].Number][Route[BestR].V[j].Number];
            if ( ArriveTime > Route[BestR].V[j].End )
                Route[BestR].SubT = Route[BestR].SubT + ArriveTime - Route[BestR].V[j].End;
            else if ( ArriveTime < Route[BestR].V[j].Begin )
                ArriveTime = Route[BestR].V[j].Begin;
        }
        ArriveTime = 0;
        Route[Customer[BestC].R].SubT = 0;
        for ( int j = 1; j < Route[Customer[BestC].R].V.size(); ++j ) {
            ArriveTime = ArriveTime + Route[Customer[BestC].R].V[j - 1].Service + Graph[Route[Customer[BestC].R].V[j - 1].Number][Route[Customer[BestC].R].V[j].Number];
            if ( ArriveTime > Route[Customer[BestC].R].V[j].End )
                Route[Customer[BestC].R].SubT = Route[Customer[BestC].R].SubT + ArriveTime - Route[Customer[BestC].R].V[j].End;
            else if ( ArriveTime < Route[Customer[BestC].R].V[j].Begin )
                ArriveTime = Route[Customer[BestC].R].V[j].Begin;
        }

        //更新被操作的节点所属路径编号
        Customer[BestC].R = BestR;

        //如果当前解合法且较优则更新存储结果
        if ( ( Check ( Route ) == true ) && ( Ans > BestV ) ) {
            Copy_Route();
            Ans = BestV;
        }
    }
}
//************************************************************
int main() {
    clock_t Start, Finish;
    //Start = clock();

    srand ( ( unsigned ) time ( NULL ) );
    ReadIn_and_Initialization();
    Construction();
    Tabu_Search();
    Output ( Route_Ans );

    //Finish = clock();
    //cout << "Total Running Time = " << ( Finish - Start ) / 1000.0 << endl;
    return 0;
}
//************************************************************

Output
//输出样例（R101.txt）
//*****************************************************************
//TheMinimum Total Distance = 1664.75
//ConcreteSchedule of Each Route as Following :
//No.1: 1 -> 46 -> 84 -> 100 -> 95 -> 97 -> 1
//No.2: 1 -> 28 -> 32 -> 89 -> 8 -> 1
//No.3: 1 -> 41 -> 54 -> 27 -> 1
//No.4: 1 -> 63 -> 12 -> 91 -> 11 -> 1
//No.5: 1 -> 3 -> 22 -> 74 -> 42 -> 57 -> 5 -> 1
//No.6: 1 -> 15 -> 45 -> 39 -> 44 -> 59 -> 1
//No.7: 1 -> 37 -> 48 -> 20 -> 9 -> 47 -> 18 -> 1
//No.8: 1 -> 13 -> 77 -> 79 -> 35 -> 36 -> 78 -> 1
//No.9: 1 -> 66 -> 72 -> 10 -> 67 -> 2 -> 1
//No.10: 1 -> 64 -> 65 -> 50 -> 49 -> 1
//No.11: 1 -> 29 -> 30 -> 80 -> 51 -> 69 -> 1
//No.12: 1 -> 40 -> 24 -> 68 -> 56 -> 26 -> 1
//No.13: 1 -> 34 -> 82 -> 4 -> 55 -> 25 -> 81 -> 1
//No.14: 1 -> 70 -> 31 -> 52 -> 21 -> 33 -> 71 -> 1
//No.15: 1 -> 96 -> 99 -> 62 -> 87 -> 92 -> 101 -> 1
//No.16: 1 -> 83 -> 19 -> 85 -> 61 -> 90 -> 1
//No.17: 1 -> 73 -> 76 -> 23 -> 75 -> 1
//No.18: 1 -> 53 -> 7 -> 1
//No.19: 1 -> 93 -> 43 -> 16 -> 88 -> 58 -> 98 -> 14 -> 1
//No.20: 1 -> 60 -> 6 -> 17 -> 86 -> 38 -> 94 -> 1
//Check_Ans= 1664.75
```
-The End-
文案 / 金鑫（研一）
排版 / 金鑫 （研一）
代码 / 汪文宇（大四）
指导老师 / 秦时明岳