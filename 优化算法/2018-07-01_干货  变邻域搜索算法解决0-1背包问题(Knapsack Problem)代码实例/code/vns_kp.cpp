#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// ��Ʒ������ ÿһ����Ʒ��0��1����ѡ�� 0����ѡ��ǰ��Ʒ 1����ѡ��ǰ��Ʒ
const int n = 100;

//�㷨����������
const int Max_Iteration = 1000;

//��������
const int MaxFlip = 3;
int flip = 1;


//�����������
const int maxWeight = 5 * n;

//��¼�Ѿ����ı�������
int solutionsChecked = 0;

//��Ʒ��Ӧ��ֵ&&����
int values[n] = { 0 };
int weights[n] = { 0 };

//���������
const int seed = 5113; //2971


/************************************************************************/
/* 
	��������ࣺ

*/
/************************************************************************/

typedef struct Knapsack_Problem_Solution
{
	int selection[n] = { 0 };  //��ǰ��������Ʒѡ����� selection[i] == 0 or 1 <==> ��ѡ�� or ѡ�� ��i����Ʒ
	int total_values = 0;      //��ǰ��������Ʒ�ܼ�ֵ
	int total_weights = 0;    //��ǰ��������Ʒ������
}KP_Solution;

//��selection[n]�������ۣ�����total_values��total_weights
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
		x.total_values = maxWeight - x.total_weights; //�����������������������ֵ����Ϊ����
	}

}


//�ھӽ⼯��
vector<KP_Solution> nbrhood;

void MySwap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//���������������ھӽ�
void neighborhood(KP_Solution &x, int flip)
{
	//������1
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
	//������2
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
	//������3
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
//������ɼ�ֵ������
void Rand_Value_Weight()
{
	for (int i = 0; i < n; i++)
	{
		values[i] = rand() % 90 + 10; // 10 - 100
		weights[i] = rand() % 15 + 5; // 5 - 20
	}
}

//������ɽ������
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
		//����λ
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

	cout << "ʯͷ����Ϊ��" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << setw(2) <<weights[i] << "  ";
		if ((i + 1) % 25 == 0)
		{
			cout << endl;
		}
	}

	cout << "\nʯͷ��ֵΪ��" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << values[i] << "  ";
		if ((i + 1) % 25 == 0)
		{
			cout << endl;
		}
	}

	cout << endl << "���ս��: �Ѽ����ܷ����� = " << solutionsChecked << endl;
	cout << "�����������Ϊ:" << maxWeight << endl;
	cout << "�ҵ�����ֵΪ: " << kpx.total_values << endl;
	cout << "������ǰ����Ϊ: " << kpx.total_weights << endl;

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