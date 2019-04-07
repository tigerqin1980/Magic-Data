#include <stdio.h>
typedef struct matrix
{
	int cost[101][101];
	int zeroelem[101][101];
 	int costforout[101][101];
 	int matrixsize;
}MATRIX;
MATRIX hungary;
int result[5041][2];								//用来储存解的结果,第一列表示工人第二列表示工件 
void zeroout(MATRIX &hungary);						//减去行列的最小值得到零元素 
void circlezero(MATRIX &hungary);					//圈出单行列零元素 
void twozero(MATRIX &hungary);						//圈出行列存在两个以上的零元素 
void judge(MATRIX &hungary,int result[2000][2]);	//判断是否符合匈牙利算法条件 
void refresh(MATRIX &hungary);						//不符合条件，对矩阵进行变形 
void output(int result[2000][2],MATRIX hungary);	//结果输出 
MATRIX input();										//初始输入 
int main()
{
	result[0][0]=0;
	hungary=input();
	zeroout(hungary);
	circlezero(hungary); 
	output(result,hungary);
}
MATRIX input()
{
	int i,j; 
	matrix hungary;
	printf("指派问题的匈牙利解法\n");
	printf("请输入cost矩阵的阶数:\n");
	scanf("%d",&hungary.matrixsize);
	printf("请输入代表工人和工件的%d阶矩阵:\n",hungary.matrixsize);
	for(i=1;i<=hungary.matrixsize;i++)
  		for(j=1;j<=hungary.matrixsize;j++)
  		{   
 			scanf("%d",&hungary.cost[i][j]);
 			hungary.costforout[i][j]=hungary.cost[i][j];
  		}

 	return hungary;
}
void zeroout(MATRIX &hungary)
{
	int i,j; 
	int tem;	//表示同行的最大元素或同列的最大元素 
	for(i=1;i<=hungary.matrixsize;i++)             //减去同行最大元素
 	{ 
  	 	tem=hungary.cost[i][1];
  	 	for(j=2;j<=hungary.matrixsize;j++)
    	if(hungary.cost[i][j]<tem)
    		tem=hungary.cost[i][j];
  		for(j=1;j<=hungary.matrixsize;j++)
   		hungary.cost[i][j]=hungary.cost[i][j]-tem;
 	}
 	for(j=1;j<=hungary.matrixsize;j++)            //减去同列最大元素
 	{
  		tem=hungary.cost[1][j];
  		for(i=2;i<=hungary.matrixsize;i++)
     	if(hungary.cost[i][j]<tem)
    		tem=hungary.cost[i][j];
  		for(i=1;i<=hungary.matrixsize;i++)
  			hungary.cost[i][j]=hungary.cost[i][j]-tem;
 	}
}
void circlezero(MATRIX &hungary)
{
	int i,j,p;  
	int flag; 
 	for(i=0;i<=hungary.matrixsize;i++)                         //在矩阵外面构建半圈矩阵标记0的个数；
  		hungary.cost[i][0]=0; 
 	for(j=1;j<=hungary.matrixsize;j++)
  		hungary.cost[0][j]=0;
 	for(i=1;i<=hungary.matrixsize;i++)
  		for(j=1;j<=hungary.matrixsize;j++)
   		if(hungary.cost[i][j]==0)
   		{
    		hungary.cost[i][0]++;
    		hungary.cost[0][j]++;
    		hungary.cost[0][0]++;
   		} 
 	for(i=0;i<=hungary.matrixsize;i++)               //新建一个矩阵
  		for(j=0;j<=hungary.matrixsize;j++)           
   			hungary.zeroelem[i][j]=0;   
 	flag=hungary.cost[0][0]+1;                         //flag = 0的总个数+1
	while(hungary.cost[0][0]<flag)                   
	{
  		flag=hungary.cost[0][0];                                       //行列单0的情况，
  		for(i=1;i<=hungary.matrixsize;i++)                             //第一遍先行后列
	 	{
   			if(hungary.cost[i][0]==1) 
			{
				for(j=1;j<=hungary.matrixsize;j++)                        
     			if(hungary.cost[i][j]==0&&hungary.zeroelem[i][j]==0)
      				break;
    			hungary.zeroelem[i][j]=1;
    			hungary.cost[i][0]--;
   		 		hungary.cost[0][j]--;
    			hungary.cost[0][0]--;
    			if(hungary.cost[0][j]>0)
     			for(p=1;p<=hungary.matrixsize;p++)
      			if(hungary.cost[p][j]==0&&hungary.zeroelem[p][j]==0)
      			{
       				hungary.zeroelem[p][j]=2;
       				hungary.cost[p][0]--;
       				hungary.cost[0][j]--;
       				hungary.cost[0][0]--;
      			}      
			}                           
	
  		}
		for(j=1;j<=hungary.matrixsize;j++)                            //   第二遍先列后行
 		{
   			if(hungary.cost[0][j]==1)
			{
		    	for(i=1;i<=hungary.matrixsize;i++)
     			if(hungary.cost[i][j]==0&&hungary.zeroelem[i][j]==0)
      				break;
    			hungary.zeroelem[i][j]=1;
    			hungary.cost[i][0]--;
    			hungary.cost[0][j]--;
    			hungary.cost[0][0]--;
    			if(hungary.cost[i][0]>0)
     			for(p=1;p<=hungary.matrixsize;p++)
      			if(hungary.cost[i][p]==0&&hungary.zeroelem[i][p]==0)
      			{
       				hungary.zeroelem[i][p]=2;
       				hungary.cost[i][0]--;
       				hungary.cost[0][p]--;
       				hungary.cost[0][0]--;
      			}
			}
  		}
	}
	if(hungary.cost[0][0]>0)
		twozero(hungary);
	else
		judge(hungary,result);
}
void judge(MATRIX &hungary,int result[5041][2])
{
	int i,j;
 	int num=0;	//线的条数 
 	int start;	//每组解的储存开始位置 
 	for(i=1;i<=hungary.matrixsize;i++)
  		for(j=1;j<=hungary.matrixsize;j++)
   		if(hungary.zeroelem[i][j]==1)
    		num++;						//划线的条数 
		if(num==hungary.matrixsize)
		{
  			start=result[0][0]*hungary.matrixsize+1;
   			for(i=1;i<=hungary.matrixsize;i++)
    			for(j=1;j<=hungary.matrixsize;j++)
     				if(hungary.zeroelem[i][j]==1)
     				{
      					result[start][0]=i;
      					result[start++][1]=j;
     				}
   					result[0][0]++;
  		}
 		else
  			refresh(hungary);
}
void twozero(MATRIX &hungary)
{
	int i,j;
	int p,q;
	int m,n;
	int flag;
    MATRIX backup;
	for(i=1;i<=hungary.matrixsize;i++)
		if(hungary.cost[i][0]>0)
			break;
	if(i<=hungary.matrixsize)
	{
		for(j=1;j<=hungary.matrixsize;j++)
		{
			backup=hungary;//备份以寻找多解 
			if(hungary.cost[i][j]==0&&hungary.zeroelem[i][j]==0)
			{
    			hungary.zeroelem[i][j]=1;
    			hungary.cost[i][0]--;
    			hungary.cost[0][j]--;
    			hungary.cost[0][0]--;
    			for(q=1;q<=hungary.matrixsize;q++)
     				if(hungary.cost[i][q]==0&&hungary.zeroelem[i][q]==0)
     				{
      					hungary.zeroelem[i][q]=2;
      					hungary.cost[i][0]--;
      					hungary.cost[0][q]--;
      					hungary.cost[0][0]--;
     				}
    			for(p=1;p<=hungary.matrixsize;p++)
     				if(hungary.cost[p][j]==0&&hungary.zeroelem[p][j]==0)
     				{
      					hungary.zeroelem[p][j]=2;
      					hungary.cost[p][0]--;
      					hungary.cost[0][j]--;
      					hungary.cost[0][0]--;
     				}
    			flag=hungary.cost[0][0]+1;
    			while(hungary.cost[0][0]<flag)
    			{
     				flag=hungary.cost[0][0];
     				for(p=i+1;p<=hungary.matrixsize;p++)
     				{
     			 		if(hungary.cost[p][0]==1)
						{
       						for(q=1;q<=hungary.matrixsize;q++)
        						if(hungary.cost[p][q]==0&&hungary.zeroelem[p][q]==0)
         							break;
       							hungary.zeroelem[p][q]=1;
       							hungary.cost[p][0]--;
       							hungary.cost[0][q]--;
       							hungary.cost[0][0]--;
       						for(m=1;m<=hungary.matrixsize;m++)
        						if(hungary.cost[m][q]==0&&hungary.zeroelem[m][q]==0)
        						{
        			 				hungary.zeroelem[m][q]=2;
         							hungary.cost[m][0]--;
         							hungary.cost[0][q]--;
         							hungary.cost[0][0]--;
        						}
      					}
     				}
     				for(q=1;q<=hungary.matrixsize;q++)
     				{
      					if(hungary.cost[0][q]==1)
						{
       						for(p=1;p<=hungary.matrixsize;p++)
        						if(hungary.cost[p][q]==0&&hungary.zeroelem[p][q]==0)
         							break;
       							hungary.zeroelem[p][q]=1;
       							hungary.cost[p][q]--;
       							hungary.cost[0][q]--;
       							hungary.cost[0][0]--;
       						for(n=1;n<=hungary.matrixsize;n++)
        						if(hungary.cost[p][n]==0&&hungary.zeroelem[p][n]==0)
								{
         							hungary.zeroelem[p][n]=2;
         							hungary.cost[p][0]--;
         							hungary.cost[0][n]--;
         							hungary.cost[0][0]--;
        						}
      					}
     				}
    			}
    			if(hungary.cost[0][0]>0)                   //确保hungary.cost[][]中的0元素都在zeroelem[][]中被完全标记出来。
     				twozero(hungary);
    			else 
     				judge(hungary,result);
   			}           
   			hungary=backup;
  		}
 	}
}
void refresh(MATRIX &hungary)
{
	int i,j,min=0;
	int flag1=0,flag2=0;
	for(i=1;i<=hungary.matrixsize;i++)
	{
		for(j=1;j<=hungary.matrixsize;j++)
		if(hungary.zeroelem[i][j]==1)
		{
			hungary.zeroelem[i][0]=1;         //有独立零元素
    		break;
   		}
	}
	while(flag1==0)
	{
		flag1=1;
		for(i=1;i<=hungary.matrixsize;i++)
			if(hungary.zeroelem[i][0]==0)
			{
				hungary.zeroelem[i][0]=2;
				for(j=1;j<=hungary.matrixsize;j++)
					if(hungary.zeroelem[i][j]==2)
					{
						hungary.zeroelem[0][j]=1;
					}
   			}
		for(j=1;j<=hungary.matrixsize;j++)
		{
			if(hungary.zeroelem[0][j]==1)
			{
				hungary.zeroelem[0][j]=2;
				for(i=1;i<=hungary.matrixsize;i++)
    				if(hungary.zeroelem[i][j]==1)
					{
						hungary.zeroelem[i][0]=0;
      					flag1=0;
     				}
   			}
  		}
 	}                    //对打勾的行和列标记成2 
	for(i=1;i<=hungary.matrixsize;i++)
	{
		if(hungary.zeroelem[i][0]==2)
		{
			for(j=1;j<=hungary.matrixsize;j++)
			{
    			if(hungary.zeroelem[0][j]!=2)
     				if(flag2==0)
     				{
     				 	min=hungary.cost[i][j];
      					flag2=1;
     				}
     			else
				{
      				if(hungary.cost[i][j]<min)
       					min=hungary.cost[i][j];
     			}
   			}        
  		}
 	}					//寻找未被覆盖的最小值 
	for(i=1;i<=hungary.matrixsize;i++)
	{
		if(hungary.zeroelem[i][0]==2)
			for(j=1;j<=hungary.matrixsize;j++)
				hungary.cost[i][j]=hungary.cost[i][j]-min;
	}
	for(j=1;j<=hungary.matrixsize;j++)
	{
		if(hungary.zeroelem[0][j]==2)
			for(i=1;i<=hungary.matrixsize;i++)
				hungary.cost[i][j]=hungary.cost[i][j]+min;
	}                   //未被划线的行减去未被覆盖的最小值，被划线的列加上未被覆盖的最小值 
	for(i=0;i<=hungary.matrixsize;i++)
		for(j=0;j<=hungary.matrixsize;j++)
			hungary.zeroelem[i][j]=0;              //矩阵清0
	circlezero(hungary); 
}
void output(int result[5041][2],MATRIX hungary)
{
	int num;	//解的数量 
	int minsum;	//最小的工作成本 
	int i,j;
	char w;
	int start;  //每个解的储存开始位置 
	minsum=0;
	for(i=1;i<=hungary.matrixsize;i++)
	{
		minsum=minsum+hungary.costforout[i][result[i][1]];
	}
	printf("最优解的目标函数值为%d.\n",minsum);
	num=result[0][0];
  	printf("有%d种解.\n",num);  
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("按任意键输出第%d种解.\n",i);
		scanf("%c",&w);
		start=(i-1)*hungary.matrixsize+1;	 
		for(j=start;j<start+hungary.matrixsize;j++)
    			printf("第%d个人做第%d件工作.\n",result[j][0],result[j][1]);
 		printf("\n");
 	}
}
#include <stdio.h>
typedef struct matrix
{
	int cost[101][101];
	int zeroelem[101][101];
 	int costforout[101][101];
 	int matrixsize;
}MATRIX;
MATRIX hungary;
int result[5041][2];								//用来储存解的结果,第一列表示工人第二列表示工件 
void zeroout(MATRIX &hungary);						//减去行列的最小值得到零元素 
void circlezero(MATRIX &hungary);					//圈出单行列零元素 
void twozero(MATRIX &hungary);						//圈出行列存在两个以上的零元素 
void judge(MATRIX &hungary,int result[2000][2]);	//判断是否符合匈牙利算法条件 
void refresh(MATRIX &hungary);						//不符合条件，对矩阵进行变形 
void output(int result[2000][2],MATRIX hungary);	//结果输出 
MATRIX input();										//初始输入 
int main()
{
	result[0][0]=0;
	hungary=input();
	zeroout(hungary);
	circlezero(hungary); 
	output(result,hungary);
}
MATRIX input()
{
	int i,j; 
	matrix hungary;
	printf("指派问题的匈牙利解法\n");
	printf("请输入cost矩阵的阶数:\n");
	scanf("%d",&hungary.matrixsize);
	printf("请输入代表工人和工件的%d阶矩阵:\n",hungary.matrixsize);
	for(i=1;i<=hungary.matrixsize;i++)
  		for(j=1;j<=hungary.matrixsize;j++)
  		{   
 			scanf("%d",&hungary.cost[i][j]);
 			hungary.costforout[i][j]=hungary.cost[i][j];
  		}

 	return hungary;
}
void zeroout(MATRIX &hungary)
{
	int i,j; 
	int tem;	//表示同行的最大元素或同列的最大元素 
	for(i=1;i<=hungary.matrixsize;i++)             //减去同行最大元素
 	{ 
  	 	tem=hungary.cost[i][1];
  	 	for(j=2;j<=hungary.matrixsize;j++)
    	if(hungary.cost[i][j]<tem)
    		tem=hungary.cost[i][j];
  		for(j=1;j<=hungary.matrixsize;j++)
   		hungary.cost[i][j]=hungary.cost[i][j]-tem;
 	}
 	for(j=1;j<=hungary.matrixsize;j++)            //减去同列最大元素
 	{
  		tem=hungary.cost[1][j];
  		for(i=2;i<=hungary.matrixsize;i++)
     	if(hungary.cost[i][j]<tem)
    		tem=hungary.cost[i][j];
  		for(i=1;i<=hungary.matrixsize;i++)
  			hungary.cost[i][j]=hungary.cost[i][j]-tem;
 	}
}
void circlezero(MATRIX &hungary)
{
	int i,j,p;  
	int flag; 
 	for(i=0;i<=hungary.matrixsize;i++)                         //在矩阵外面构建半圈矩阵标记0的个数；
  		hungary.cost[i][0]=0; 
 	for(j=1;j<=hungary.matrixsize;j++)
  		hungary.cost[0][j]=0;
 	for(i=1;i<=hungary.matrixsize;i++)
  		for(j=1;j<=hungary.matrixsize;j++)
   		if(hungary.cost[i][j]==0)
   		{
    		hungary.cost[i][0]++;
    		hungary.cost[0][j]++;
    		hungary.cost[0][0]++;
   		} 
 	for(i=0;i<=hungary.matrixsize;i++)               //新建一个矩阵
  		for(j=0;j<=hungary.matrixsize;j++)           
   			hungary.zeroelem[i][j]=0;   
 	flag=hungary.cost[0][0]+1;                         //flag = 0的总个数+1
	while(hungary.cost[0][0]<flag)                   
	{
  		flag=hungary.cost[0][0];                                       //行列单0的情况，
  		for(i=1;i<=hungary.matrixsize;i++)                             //第一遍先行后列
	 	{
   			if(hungary.cost[i][0]==1) 
			{
				for(j=1;j<=hungary.matrixsize;j++)                        
     			if(hungary.cost[i][j]==0&&hungary.zeroelem[i][j]==0)
      				break;
    			hungary.zeroelem[i][j]=1;
    			hungary.cost[i][0]--;
   		 		hungary.cost[0][j]--;
    			hungary.cost[0][0]--;
    			if(hungary.cost[0][j]>0)
     			for(p=1;p<=hungary.matrixsize;p++)
      			if(hungary.cost[p][j]==0&&hungary.zeroelem[p][j]==0)
      			{
       				hungary.zeroelem[p][j]=2;
       				hungary.cost[p][0]--;
       				hungary.cost[0][j]--;
       				hungary.cost[0][0]--;
      			}      
			}                           
	
  		}
		for(j=1;j<=hungary.matrixsize;j++)                            //   第二遍先列后行
 		{
   			if(hungary.cost[0][j]==1)
			{
		    	for(i=1;i<=hungary.matrixsize;i++)
     			if(hungary.cost[i][j]==0&&hungary.zeroelem[i][j]==0)
      				break;
    			hungary.zeroelem[i][j]=1;
    			hungary.cost[i][0]--;
    			hungary.cost[0][j]--;
    			hungary.cost[0][0]--;
    			if(hungary.cost[i][0]>0)
     			for(p=1;p<=hungary.matrixsize;p++)
      			if(hungary.cost[i][p]==0&&hungary.zeroelem[i][p]==0)
      			{
       				hungary.zeroelem[i][p]=2;
       				hungary.cost[i][0]--;
       				hungary.cost[0][p]--;
       				hungary.cost[0][0]--;
      			}
			}
  		}
	}
	if(hungary.cost[0][0]>0)
		twozero(hungary);
	else
		judge(hungary,result);
}
void judge(MATRIX &hungary,int result[5041][2])
{
	int i,j;
 	int num=0;	//线的条数 
 	int start;	//每组解的储存开始位置 
 	for(i=1;i<=hungary.matrixsize;i++)
  		for(j=1;j<=hungary.matrixsize;j++)
   		if(hungary.zeroelem[i][j]==1)
    		num++;						//划线的条数 
		if(num==hungary.matrixsize)
		{
  			start=result[0][0]*hungary.matrixsize+1;
   			for(i=1;i<=hungary.matrixsize;i++)
    			for(j=1;j<=hungary.matrixsize;j++)
     				if(hungary.zeroelem[i][j]==1)
     				{
      					result[start][0]=i;
      					result[start++][1]=j;
     				}
   					result[0][0]++;
  		}
 		else
  			refresh(hungary);
}
void twozero(MATRIX &hungary)
{
	int i,j;
	int p,q;
	int m,n;
	int flag;
    MATRIX backup;
	for(i=1;i<=hungary.matrixsize;i++)
		if(hungary.cost[i][0]>0)
			break;
	if(i<=hungary.matrixsize)
	{
		for(j=1;j<=hungary.matrixsize;j++)
		{
			backup=hungary;//备份以寻找多解 
			if(hungary.cost[i][j]==0&&hungary.zeroelem[i][j]==0)
			{
    			hungary.zeroelem[i][j]=1;
    			hungary.cost[i][0]--;
    			hungary.cost[0][j]--;
    			hungary.cost[0][0]--;
    			for(q=1;q<=hungary.matrixsize;q++)
     				if(hungary.cost[i][q]==0&&hungary.zeroelem[i][q]==0)
     				{
      					hungary.zeroelem[i][q]=2;
      					hungary.cost[i][0]--;
      					hungary.cost[0][q]--;
      					hungary.cost[0][0]--;
     				}
    			for(p=1;p<=hungary.matrixsize;p++)
     				if(hungary.cost[p][j]==0&&hungary.zeroelem[p][j]==0)
     				{
      					hungary.zeroelem[p][j]=2;
      					hungary.cost[p][0]--;
      					hungary.cost[0][j]--;
      					hungary.cost[0][0]--;
     				}
    			flag=hungary.cost[0][0]+1;
    			while(hungary.cost[0][0]<flag)
    			{
     				flag=hungary.cost[0][0];
     				for(p=i+1;p<=hungary.matrixsize;p++)
     				{
     			 		if(hungary.cost[p][0]==1)
						{
       						for(q=1;q<=hungary.matrixsize;q++)
        						if(hungary.cost[p][q]==0&&hungary.zeroelem[p][q]==0)
         							break;
       							hungary.zeroelem[p][q]=1;
       							hungary.cost[p][0]--;
       							hungary.cost[0][q]--;
       							hungary.cost[0][0]--;
       						for(m=1;m<=hungary.matrixsize;m++)
        						if(hungary.cost[m][q]==0&&hungary.zeroelem[m][q]==0)
        						{
        			 				hungary.zeroelem[m][q]=2;
         							hungary.cost[m][0]--;
         							hungary.cost[0][q]--;
         							hungary.cost[0][0]--;
        						}
      					}
     				}
     				for(q=1;q<=hungary.matrixsize;q++)
     				{
      					if(hungary.cost[0][q]==1)
						{
       						for(p=1;p<=hungary.matrixsize;p++)
        						if(hungary.cost[p][q]==0&&hungary.zeroelem[p][q]==0)
         							break;
       							hungary.zeroelem[p][q]=1;
       							hungary.cost[p][q]--;
       							hungary.cost[0][q]--;
       							hungary.cost[0][0]--;
       						for(n=1;n<=hungary.matrixsize;n++)
        						if(hungary.cost[p][n]==0&&hungary.zeroelem[p][n]==0)
								{
         							hungary.zeroelem[p][n]=2;
         							hungary.cost[p][0]--;
         							hungary.cost[0][n]--;
         							hungary.cost[0][0]--;
        						}
      					}
     				}
    			}
    			if(hungary.cost[0][0]>0)                   //确保hungary.cost[][]中的0元素都在zeroelem[][]中被完全标记出来。
     				twozero(hungary);
    			else 
     				judge(hungary,result);
   			}           
   			hungary=backup;
  		}
 	}
}
void refresh(MATRIX &hungary)
{
	int i,j,min=0;
	int flag1=0,flag2=0;
	for(i=1;i<=hungary.matrixsize;i++)
	{
		for(j=1;j<=hungary.matrixsize;j++)
		if(hungary.zeroelem[i][j]==1)
		{
			hungary.zeroelem[i][0]=1;         //有独立零元素
    		break;
   		}
	}
	while(flag1==0)
	{
		flag1=1;
		for(i=1;i<=hungary.matrixsize;i++)
			if(hungary.zeroelem[i][0]==0)
			{
				hungary.zeroelem[i][0]=2;
				for(j=1;j<=hungary.matrixsize;j++)
					if(hungary.zeroelem[i][j]==2)
					{
						hungary.zeroelem[0][j]=1;
					}
   			}
		for(j=1;j<=hungary.matrixsize;j++)
		{
			if(hungary.zeroelem[0][j]==1)
			{
				hungary.zeroelem[0][j]=2;
				for(i=1;i<=hungary.matrixsize;i++)
    				if(hungary.zeroelem[i][j]==1)
					{
						hungary.zeroelem[i][0]=0;
      					flag1=0;
     				}
   			}
  		}
 	}                    //对打勾的行和列标记成2 
	for(i=1;i<=hungary.matrixsize;i++)
	{
		if(hungary.zeroelem[i][0]==2)
		{
			for(j=1;j<=hungary.matrixsize;j++)
			{
    			if(hungary.zeroelem[0][j]!=2)
     				if(flag2==0)
     				{
     				 	min=hungary.cost[i][j];
      					flag2=1;
     				}
     			else
				{
      				if(hungary.cost[i][j]<min)
       					min=hungary.cost[i][j];
     			}
   			}        
  		}
 	}					//寻找未被覆盖的最小值 
	for(i=1;i<=hungary.matrixsize;i++)
	{
		if(hungary.zeroelem[i][0]==2)
			for(j=1;j<=hungary.matrixsize;j++)
				hungary.cost[i][j]=hungary.cost[i][j]-min;
	}
	for(j=1;j<=hungary.matrixsize;j++)
	{
		if(hungary.zeroelem[0][j]==2)
			for(i=1;i<=hungary.matrixsize;i++)
				hungary.cost[i][j]=hungary.cost[i][j]+min;
	}                   //未被划线的行减去未被覆盖的最小值，被划线的列加上未被覆盖的最小值 
	for(i=0;i<=hungary.matrixsize;i++)
		for(j=0;j<=hungary.matrixsize;j++)
			hungary.zeroelem[i][j]=0;              //矩阵清0
	circlezero(hungary); 
}
void output(int result[5041][2],MATRIX hungary)
{
	int num;	//解的数量 
	int minsum;	//最小的工作成本 
	int i,j;
	char w;
	int start;  //每个解的储存开始位置 
	minsum=0;
	for(i=1;i<=hungary.matrixsize;i++)
	{
		minsum=minsum+hungary.costforout[i][result[i][1]];
	}
	printf("最优解的目标函数值为%d.\n",minsum);
	num=result[0][0];
  	printf("有%d种解.\n",num);  
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("按任意键输出第%d种解.\n",i);
		scanf("%c",&w);
		start=(i-1)*hungary.matrixsize+1;	 
		for(j=start;j<start+hungary.matrixsize;j++)
    			printf("第%d个人做第%d件工作.\n",result[j][0],result[j][1]);
 		printf("\n");
 	}
}