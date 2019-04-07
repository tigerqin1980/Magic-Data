/*
	Author:Sun Jiaxuan
	School:Huazhong University of Science and Technology
	Compiler:TDM-GCC 4.7.1 64-bit Release
	Time:2017-10-11 16:00
*/

#include <iostream>
#include <stdio.h>
#define maxsize 10000
#define maxsize_n 100
#define max 1000                                         //实际问题中出现的运费不能超过max，即max为最大运费 
using namespace std;
typedef struct node
{
       int x;
       int y;
       int pre;                                                     //pre表示指向它的前一结点 
       int flag;                                                    //flag表示搜索行（或列）的状态，取值为0、1,其中1表示行搜索，0表示列搜索。 
}sqtype;
FILE *fp1,*fp2;			                                            //文件定义
sqtype sq[maxsize];
int circle[maxsize_n][maxsize_n];   //二维数组存储数据
int flag[maxsize_n][maxsize_n];     //用于存储判断circle对应位置的状态，0为初始状态，1表示基变量所在位置，2表示在进行最小元素法时被划去。
int front,rear;                     //队列的头指针和为指针。 

int base_array[maxsize_n][maxsize_n];                        //base_array矩阵用于物品的调运方案 
        
int m,n;
typedef struct node1
{
     int x;                                         //x用于记录最小元素所在位置的行坐标 
     int y;                                         //y用于记录最小元素所在位置的列坐标 
     int min_flag;                                  //min_flag用于记录最小元素所在位置的状态，数值上等于flag数组里的对应元素 
}min_num;

void min_method(int m,int n)						//求初始基，方法为最小元素法 
{
     int i,j,k;
     min_num temp_min,temp_min1;
     for (i=1;i<=m;i++)                              //初始化 
     {
         for (j=1;j<=n;j++)
         {
             base_array[i][j]=0;
             flag[i][j]=0;                          //标记每个位置的元素都没有被处理 
         }
     } 
     for (k=1;k<=m+n-1;k++)                         //最多循环m+n-1次，因为基变量的个数为m+n-1； 
     {
         temp_min.min_flag=max;
         temp_min.x=0;
         temp_min.y=0;
         //下面的两重循环的作用是找到没有处理元素中的最小元素 
         for (i=1;i<=m;i++)
         {
             for (j=1;j<=n;j++)
             {
                 if ( (flag[i][j]==0) && (circle[i][j]<temp_min.min_flag) )                      //该点所在位置没有处理，并且该点所在位置的运费比记录的小 
                 {
                    temp_min.x=i;
                    temp_min.y=j;
                    temp_min.min_flag=circle[i][j];
                 }
             }
         }
         //下面对前面找到的最小元素所在的行或列进行处理
         if (circle[temp_min.x][n+1]>circle[m+1][temp_min.y])             //该最小元素所在位置的行元素（销量）比行元素（产量）大 
         {
             for (i=1;i<=m;i++)
             {
                 if (flag[i][temp_min.y]==0)                              //表示该位置没有被处理 
                 {
                    flag[i][temp_min.y]=2;                                //标记该列的所有元素划去 
                 }
             }
             flag[temp_min.x][temp_min.y]=1;                              //标记最小元素所在位置为基变量所在位置 
             base_array[temp_min.x][temp_min.y]=circle[m+1][temp_min.y];  //更新调运方案矩阵 
             circle[temp_min.x][n+1]-=circle[m+1][temp_min.y];
             circle[m+1][temp_min.y]=0;
         }
         else if (circle[temp_min.x][n+1]<circle[m+1][temp_min.y])             //该最小元素所在位置的行元素（销量）比行元素（产量）小 
         {
             for (j=1;j<=n;j++)
             {
                 if (flag[temp_min.x][j]==0)                                   //表示该位置没有被处理
                 {
                    flag[temp_min.x][j]=2;                                   //标记该列的所有元素划去 
                 }
             }
             flag[temp_min.x][temp_min.y]=1;                              //标记最小元素所在位置为基变量所在位置 
             base_array[temp_min.x][temp_min.y]=circle[temp_min.x][n+1];  //更新调运方案矩阵 
             circle[m+1][temp_min.y]-=circle[temp_min.x][n+1];
             circle[temp_min.x][n+1]=0;
         }
         else                                                             //该最小元素所在位置的行元素（销量）与行元素（产量）相同 
         {
             flag[temp_min.x][temp_min.y]=1;                              //标记最小元素所在位置为基变量所在位置 
             base_array[temp_min.x][temp_min.y]=circle[m+1][temp_min.y];  //更新调运方案矩阵 
             circle[m+1][temp_min.y]=0;
             circle[temp_min.x][n+1]=0;
             //为了减少调整次数，应该在最小运费上添加0,一种理念，减少迭代次数 
             temp_min1.min_flag=max;
             temp_min1.x=0;
             temp_min1.y=0;
             for (i=1;i<=m;i++)
             {
                 if ( (circle[i][temp_min.y]<temp_min1.min_flag) && (flag[i][temp_min.y]==0) )
                 {
                     temp_min1.min_flag=circle[i][temp_min.y];
                     temp_min1.x=i;
                     temp_min1.y=temp_min.y;
                 }
             }
             for (j=1;j<=n;j++)
             {
                 if ( (circle[temp_min.x][j]<temp_min1.min_flag) && (flag[temp_min.x][j]==0) )
                 {
                     temp_min1.min_flag=circle[temp_min.x][j];
                     temp_min1.x=temp_min.x;
                     temp_min1.y=j;
                 }
             }
             flag[temp_min1.x][temp_min1.y]=1;                      //在最小元素所在的位置上画0，即flag的相应位置赋值1
             for (i=1;i<=m;i++)
             {
                 if (flag[i][temp_min.y]==0)                                 //表示该位置没有被处理
                 {  
                    flag[i][temp_min.y]=2;                                   //标记该列的所有元素划去 
                 }
             }
             for (j=1;j<=n;j++)
             {
                 if (flag[temp_min.x][j]==0)                                 //表示该位置没有被处理
                 { 
                    flag[temp_min.x][j]=2;                                   //标记该列的所有元素划去 
                 } 
             }
             
         }
     }
}

void restore(int m,int n)							//将求闭回路后flag数组中改变的状态复原 
{
     int i,j;
     for (i=1;i<=m;i++)
     {
         for (j=0;j<=n;j++)
         {
             if (flag[i][j]==-1)
             {
                   flag[i][j]=1;
             }
         }
     }
}

int printpath(void)                                 //将求得的闭回路写到输出文件中并输出到缓存文件temp_close中 
{
     int i;
     FILE *fp3;
     i=rear;
     if ((fp3=fopen("temp_close.txt","w+"))==NULL) 
     {
         cout<<"File open fail!\n"<<endl;
         return 0;
     }
     fputc('#',fp3);fputc('\n',fp3);
     do{
            printf("(%d,%d)\n",sq[i].x,sq[i].y);
            fputc(sq[i].x+'0',fp3);fputc(' ',fp3);fputc(sq[i].y+'0',fp3);fputc('\n',fp3);
            i=sq[i].pre;                                            //找前一个结点 
     }while(i!=0);
     cout<<"上面的点构成一个闭回路，是起点为最后一个点。"<<endl; 
     fclose(fp3);                                                  //i=0为入口
}

int close_loop(int m,int n,int m1,int n1)           //利用回溯法确定从已知结点出发的闭回路，m,n表示矩阵的规模，m1,n1表示开始结点
{
    int i,j,x,y;
    cout<<endl;
    sq[1].x=m1;sq[1].y=n1;sq[1].pre=0;sq[1].flag=1;                  //开始结点 
    front=1;rear=1;
    while(front<=rear)												//队列非空
    {
        x=sq[front].x;y=sq[front].y;                  //开始结点
        if (sq[front].flag==1)                        //表示进行行搜索 
        {
            i=x;
            for (j=1;j<=n;j++)
                {                                                
                if (flag[i][j]==1)
                    {
                        rear++;
                        sq[rear].x=i;//记录数据
                        sq[rear].y=j;
                        sq[rear].pre=front;//记录前一个节点
                        sq[rear].flag=0;   //标志为下次进行列搜索 
                        flag[i][j]=-1;   //标记(i,j)已经达到，防止在重复
                        if (sq[rear].y==n1)
                          {
                            printpath();
                            restore(m,n);
                            return 1;
                          }
                    }
                }
        } 
        else                                          //表示进行列搜索 
        {
        	j=y;
            for (i=1;i<=m;i++)
            {
                if (flag[i][j]==1)
                {
                	rear++;
                    sq[rear].x=i;
                    sq[rear].y=j;
                    sq[rear].pre=front;
                    sq[rear].flag=1;   //标志为下次进行行搜索 
                    flag[i][j]=-1;   //标记(i,j)已经达到，防止在重复
                }
                                                
            }
        }
    front++; 
    }
    
}

int close_method()									//利用闭回路法确定非基变量的检验数 
{
     int i,j,temp,sum,x,y,flag1;
     char c;
     FILE *fp3;
     
     for (i=1;i<=m;i++)
     {
         for (j=1;j<=n;j++)
         {
             
             if (flag[i][j]==2)
             {
                  if (close_loop(m,n,i,j)==1)	//如果为非基变量，则找出其闭回路，并计算检验数 
                  {
                         sum=0;
                         flag1=1;
                         if ((fp3=fopen("temp_close.txt","r"))==NULL) 
                         {
                                cout<<"File open fail!\n"<<endl;
                                return 0;
                         }
                         c=fgetc(fp3);
                         while(c!=EOF)
                         {   
                                   fscanf(fp3,"%d",&x);
                                   if( (c=fgetc(fp3))==EOF )
                                   {
                                         break;
                                   }
                                   fscanf(fp3,"%d",&y);
                                   c=fgetc(fp3);
                                    if (flag1==1)		//设非基变量为1，依次对检验数进行增减操作 
                                   {
                                         sum+=circle[x][y];
                                         flag1=0;
                                   }
                                   else
                                   {
                                         sum-=circle[x][y];
                                         flag1=1;
                                   }
                         }
                         //cout<<"x="<<x<<"y="<<y<<endl;
                         sum+=circle[x][y]; 
                         base_array[i][j]=circle[i][j]-sum;
                  }
             }
         }
     }
     fclose(fp3);
}

min_num if_negative()								//判断非基变量的检验数是否全为正，函数返回检验数最小的数以及它所在的位置 
{
       int i,j;
       min_num nege_min;
       nege_min.min_flag=max;                                                          //初始化最小检验数记录值 
       nege_min.x=0;
       nege_min.y=0; 
       for (i=1;i<=m;i++)
       {
           for (j=1;j<=n;j++)
           {
               if ( (flag[i][j]==2) && (base_array[i][j]<nege_min.min_flag) ) 
               {
                    nege_min.x=i;
                    nege_min.y=j;
                    nege_min.min_flag=base_array[i][j];			//出现更小的检验数的点，更新nege_min 
               }
           }
       }
       return nege_min;
}

int close_adjust(int i,int j)                       //close_adjust()函数的作用是利用闭回路法调整基变量，使其更接近最优解 
{
     int x,y,flag1=1,num1=-1,num2=-1,ii,jj,main_flag=1;                                       //num1用于存储闭回路中的结点个数
     //main_flag的作用是作为基变量变为非基变量的一个状态位，取值为0或1，设置这个状态位是为了保证只有一个非基变量变为基变量 
     char c;
     min_num temp;
     FILE *fp3;
     temp.min_flag=max;                                                            //初始化 
     temp.x=0;
     temp.y=0;
     
     close_loop(m,n,i,j);
     
     
     if ((fp3=fopen("temp_close.txt","r"))==NULL) //找到闭回路中基数位置上所有基变量运量中的最小值，为做闭回路调整做准备 
     {
         cout<<"File open fail!\n"<<endl;
         return 0;
     }
     c=fgetc(fp3);
      while(c!=EOF)
     {
        num1++;                                                                           //统计闭回路中结点的个数  
        fscanf(fp3,"%d",&x);
        if( (c=fgetc(fp3))==EOF )
        {
            break;
        }
        fscanf(fp3,"%d",&y);
        c=fgetc(fp3);
        if ( (flag1==1) && (flag[x][y]==1) )
        {
           if(base_array[x][y]<=temp.min_flag)
           {
                temp.min_flag=base_array[x][y];
                temp.x=x;
                temp.y=y;
           }
           flag1=0;
        }
        else
        {
            flag1=1;
        }
     }
     fclose(fp3);
     
     //在前面找到的最小值和位置的基础上利用闭回路进行调整
     flag1=1;
     if ((fp3=fopen("temp_close.txt","r"))==NULL) 
     {
         cout<<"File open fail!\n"<<endl;
         return 0;
     }
     c=fgetc(fp3);
     while(c!=EOF)
     {
        num2++;  
        fscanf(fp3,"%d",&x);
        if( (c=fgetc(fp3))==EOF )
        {
            break;
        }
        fscanf(fp3,"%d",&y);
        c=fgetc(fp3);
        if (flag1==1)
        {
           base_array[x][y]-=temp.min_flag;
           flag1=0;
           if ( (base_array[x][y]==0) && (main_flag==1) )
           {
               flag[x][y]=2;                                    //基变量变为非基变量
               main_flag=0;                                     //状态从1变为0，表示已经有一个基变量变为非基变量，其它的基变量即使满足条件也不能变为非基变量 
           }
        }
        else
        {
            if (num2==num1-1)
            {
                 flag[x][y]=1;
                 base_array[x][y]=temp.min_flag;
            }
            else
            {
                base_array[x][y]+=temp.min_flag;
            }
            flag1=1;
        }
     }
     fclose(fp3);
}



//主函数 
main()
{
       int i,j,k=1,sum;
       min_num min;
       char c;
       if ( ((fp1=fopen("in.txt","r"))==NULL) || ((fp2=fopen("out.txt","w"))==NULL) )
       {
            cout<<"File open fail!\n"<<endl;
            return 0;
       }
       c=fgetc(fp1);		//文件读入 
       while (c=='#')
       {
             fscanf(fp1,"%d %d",&m,&n);
             cout<<"m="<<m<<"n="<<n<<endl;
             sum=0;
             for (i=1;i<=m;i++)
             {
                 for (j=1;j<=n;j++)
                 {
                         fscanf(fp1,"%d",&circle[i][j]);
                 }
             }
             for (i=1;i<=m;i++)
             {
                 fscanf(fp1,"%d",&circle[i][n+1]);
             }
             for (j=1;j<=n;j++)
             {
                 fscanf(fp1,"%d",&circle[m+1][j]);
             }
             circle[m+1][n+1]=0;		//完成运输问题矩阵的建立，包括运价与供应量需求量 
             
             for (i=1;i<=m+1;i++)
             {
                 for (j=1;j<=n+1;j++)
                 {
                         cout<<circle[i][j]<<'\t';
                 }
                 cout<<endl;
             }
             
             c=fgetc(fp1);
             min_method(m,n);
             close_method();
             min=if_negative();
             while ( min.min_flag<0 )	//如果存在最小检验数小于0，继续进行调整 
             {
                   close_adjust(min.x,min.y);
                   close_method();         
                   min=if_negative();
             }
             fputs("最终调运方案为：\n",fp2);
             cout<<"最终调运方案为：\n";
             for (i=1;i<=m;i++)
             {
                 for (j=1;j<=n;j++)
                 {
                     if (flag[i][j]==1)
                     {
                             fprintf(fp2,"%d\t",base_array[i][j]);
                             cout<<base_array[i][j]<<'\t'; 	//输出最终结果 
                     }
                     else
                     {
                         fprintf(fp2,"0\t");
                         cout<<"0\t";
                     }
                 }
                 fprintf(fp2,"\n");
                 cout<<endl;
             }
             fputs("最优值为：\n",fp2);
             cout<<"最优值为：\n";
             for (i=1;i<=m;i++)
             {
                 for (j=1;j<=n;j++)
                 {
                     if (flag[i][j]==1)
                     {
                            sum+=base_array[i][j]*circle[i][j];//计算总价格：数量*单位运价 
                     }
                 }
             }
             cout<<sum<<endl;
             fprintf(fp2,"%d\n",sum); 
             c=fgetc(fp1);
             fgetc(fp1);
      }
      
      fclose(fp1);
      fclose(fp2);
}
/*Sample Input
#
3 4
10 2 20 11
12 7 9 20
2 14 16 18
15 25 5
5 15 15 10 

第一行两个数字分别表示供应方数量和需求方数量
后面三行通过二维表的方式记录每个供应方到需求方的运价
最后两行分别表示每个供应方的最大供应量和每个需求方的最大需求量 
*/ 