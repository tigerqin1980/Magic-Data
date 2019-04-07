##00前排吹水

经过小编这几天冒着挂科的风险，日日修炼，终于赶在考试周中又给大家更新了一篇干货文章。关于用变邻域搜索解决0-1背包问题的代码。怎样，大家有没有很感动？

![](https://i.imgur.com/1gE84Hs.jpg)


##01什么是0-1背包问题？

>0-1 背包问题：给定 n 种物品和一个容量为 C 的背包，物品 i 的重量是 w_i，其价值为 v_i 。
问：应该如何选择装入背包的物品，使得装入背包中的物品的总价值最大？
为什么叫0-1背包问题呢？显然，面对每个物品，我们只有选择拿取或者不拿两种选择，不能选择装入某物品的一部分，也不能装入同一物品多次。拿就是1，不拿就是0。因此，就叫0-1背包问题。So simple, so naive. 

![](https://i.imgur.com/i2L9LoV.jpg)



##02代码小讲解

下面就几个邻域小动作给大家讲解一下。

![](https://i.imgur.com/EwdIyu0.jpg)


###解决方案设计

假设我们面前有n种物品，那么我们可以将解决方案设置成一个一维数组selection[n]。数组weights[n]表示重量，数组values[n]表示价值。

>selection[i] = 1 表示装入第i个物品。
selection[i] = 0 表示不装入第i个物品。
总价值total_value  = selection[i] * values[i]。 (i=1,2,3,4……n)
总重量total_weight = selection[i] * weights[i]。(i=1,2,3,4……n)

###邻域动作1

将解决方案selection[n]的第i位取反(i=1,2,3,4……n)。比如：

>有方案0010，那么生成的邻居解则有1010(第一位取反)、0110(第二位取反)、0000(第三位取反)、0011(第四位取反)。
不知道这么通俗易懂的大家understand了没有。

###邻域动作2

对于解决方案selection[n]，在第i  (i=1,2,3,4……n)位取反的情况下，依次将第j  (j=i+1,2,3,4……n)位也取反。还是for 一个 example吧。

对于解决方案0010。产生的邻居解如下：

![](https://i.imgur.com/QqMoPHI.png)



###邻域动作3

交换第i位和第i-3位的数。如果i<3。就交换最后的，比如：

selection[0]和selection[n-1]交换。
selection[1]和selection[n-2]交换。
selection[2]和selection[n-3]交换。

###shaking程序

这个比较简单，随机取反一些位就行了。
##背包问题的代码
```
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// 物品的数量 每一个物品有0和1两种选择 0代表选择当前物品 1代表不选择当前物品
const int n = 100;

//算法最大迭代次数
const int Max_Iteration = 1000;

//邻域数量
const int MaxFlip = 3;
int flip = 1;


//背包最大容量
const int maxWeight = 5 * n;

//记录已经检查的背包数量
int solutionsChecked = 0;

//物品对应价值&&重量
int values[n] = { 0 };
int weights[n] = { 0 };

//随机数种子
const int seed = 5113; //2971


/************************************************************************/
/* 
	解决方案类：

*/
/************************************************************************/

typedef struct Knapsack_Problem_Solution
{
	int selection[n] = { 0 };  //当前方案的物品选择情况 selection[i] == 0 or 1 <==> 不选择 or 选择 第i个物品
	int total_values = 0;      //当前方案下物品总价值
	int total_weights = 0;    //当前方案下物品总重量
}KP_Solution;

//对selection[n]进行评价，计算total_values和total_weights
void Evaluate_Solution(KP_Solution & x)
{
	x.total_values = 0;
	x.total_weights = 0;
	for (int i = 0; i < n; i++)
	{
		x.total_values += x.selection[i] * values[i];
		x.total_weights += x.selection[i] * weights[i];
	}

	if (x.total_weights > maxWeight)
	{
		x.total_values = maxWeight - x.total_weights; //超过背包最大容纳重量，价值设置为负数
	}

}


//邻居解集合
vector<KP_Solution> nbrhood;

void MySwap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//利用邻域动作生成邻居解
void neighborhood(KP_Solution &x, int flip)
{
	//邻域动作1
	if (flip == 1)
	{
		nbrhood.clear();
		for (int i = 0; i < n; i++)
		{
			nbrhood.push_back(x);
			if (nbrhood[i].selection[i] == 1)
			{
				nbrhood[i].selection[i] = 0;
			}
			else
			{
				nbrhood[i].selection[i] = 1;
			}
		}
	}
	//邻域动作2
	else if (flip == 2)
	{
		nbrhood.clear();
		int a = -1;
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				if (i != j)
				{
					a += 1;
					nbrhood.push_back(x);

					if (nbrhood[a].selection[i] == 1)
					{
						nbrhood[a].selection[i] = 0;
					}
					else
					{
						nbrhood[a].selection[i] = 1;
					}

					if (nbrhood[a].selection[j] == 1)
					{
						nbrhood[a].selection[j] = 0;
					}
					else
					{
						nbrhood[a].selection[j] = 1;
					}

				}
			}
		}
	}
	//邻域动作3
	else
	{
		nbrhood.clear();
		for (int i = 0; i < n; i++)
		{
			nbrhood.push_back(x);
			if ( i < 3)
			{
				MySwap(nbrhood[i].selection[i], nbrhood[i].selection[n + i - 3]);
			}
			else
			{
				MySwap(nbrhood[i].selection[i], nbrhood[i].selection[i - 3]);
			}
		}
	}


}
//随机生成价值和重量
void Rand_Value_Weight()
{
	for (int i = 0; i < n; i++)
	{
		values[i] = rand() % 90 + 10; // 10 - 100
		weights[i] = rand() % 15 + 5; // 5 - 20
	}
}

//随机生成解决方案
void Random_Solution(KP_Solution &x)
{
	x.total_values = 0;
	x.total_weights = 0;
	for (int i = 0; i < n; i++)
	{
		double rate = (rand() % 100) / 100.0;
		if ( rate < 0.8 )
		{
			x.selection[i] = 0;
		}
		else
		{
			x.selection[i] = 1;
		}
	}
}

void Variable_Neighborhood_Descent(KP_Solution &x)
{
	int flip = 1;
	KP_Solution x_curr;
	while ( flip < MaxFlip + 1)
	{
		neighborhood(x, flip);
		x_curr = nbrhood[0];
		Evaluate_Solution(x_curr);

		for(unsigned int i = 1; i < nbrhood.size(); i++)
		{
			solutionsChecked += 1;

			Evaluate_Solution(nbrhood[i]);

			if (nbrhood[i].total_values > x_curr.total_values)
			{
				x_curr = nbrhood[i];
			}
		}
		//邻域复位
		if (x_curr.total_weights > x.total_weights)
		{
			x = x_curr;
			flip = 1;
		}
		else
		{
			flip += 1;
		}
	}
}




void Shaking_Procdure(KP_Solution &x)
{

	int num = rand() % (n / 10) + 3; // 3 - 8
	for (int i = 0; i < num; i++)
	{
		int pos = rand() % n;
		if (x.selection[i] == 0)
		{
			x.selection[i] = 1;
		}
		else
		{
			x.selection[i] = 0;
		}
	}

	Evaluate_Solution(x);
}

void Variable_Neighborhood_Search(KP_Solution &x, int iteration)
{
	KP_Solution best = x;
	Variable_Neighborhood_Descent(best);
	for (int i = 0; i < iteration; i++)
	{
		Shaking_Procdure(x);

		Variable_Neighborhood_Descent(x);
		if (best.total_values < x.total_values)
		{
			best = x;
		}
	}

	x = best;
}

int main()
{
	srand(seed);

	KP_Solution kpx;

	Rand_Value_Weight();

	Random_Solution(kpx);

	Variable_Neighborhood_Search(kpx, Max_Iteration);

	cout << "石头重量为：" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << setw(2) <<weights[i] << "  ";
		if ((i + 1) % 25 == 0)
		{
			cout << endl;
		}
	}

	cout << "\n石头价值为：" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << values[i] << "  ";
		if ((i + 1) % 25 == 0)
		{
			cout << endl;
		}
	}

	cout << endl << "最终结果: 已检查的总方案数 = " << solutionsChecked << endl;
	cout << "背包最大容量为:" << maxWeight << endl;
	cout << "找到最大价值为: " << kpx.total_values << endl;
	cout << "背包当前重量为: " << kpx.total_weights << endl;

	for (int i = 0; i < n; i++)
	{
		cout << kpx.selection[i] << "  ";
		if ((i+1) % 25 == 0)
		{
			cout << endl;
		}
	}

	return 0;
}
```

-The End-
文案 / 邓发珩（大一）
排版 / 邓发珩（大一）
代码 / 邓发珩（大一）
审核 / 贺兴（大三）
指导老师 / 秦时明岳