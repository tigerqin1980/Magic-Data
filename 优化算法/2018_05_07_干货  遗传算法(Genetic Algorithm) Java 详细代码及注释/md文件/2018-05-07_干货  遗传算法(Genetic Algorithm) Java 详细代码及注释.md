# 代码说明

##遗传算法解决TSP旅行商问题

算法分为4个类：

GeneticAlgorithm
SpeciesIndividual
SpeciesPopulation
TSPData

数据规模: 10 cities, 20 cities and 31 cities.

###类说明：

GeneticAlgorithm:    遗传算法的主体部分，包括选择、交叉、变异
SpeciesIndividual:    物种个体类
SpeciesPopulation:  物种种群类
TSPData：                TSP数据类
MainRun：                主函数运行类

运行平台：
eclipse + windows10
![](https://i.imgur.com/r05fkC4.jpg)




详细代码
MainRun.java

主函数运行类，也就是程序入口。在这里创建算法类，创建种群，并开始运行我们的算法。得出结果以后，打印出来。

package GeneticTSP;

```
/**
 * 主函数运行类
 */

public class MainRun {

    public static void main(String[] args) {
        // TODO Auto-generated method stub

        //创建遗传算法驱动对象
        GeneticAlgorithm GA=new GeneticAlgorithm();

        //创建初始种群
        SpeciesPopulation speciesPopulation = new SpeciesPopulation();

        //开始遗传算法（选择算子、交叉算子、变异算子）
        SpeciesIndividual bestRate=GA.run(speciesPopulation);

        //打印路径与最短距离
        bestRate.printRate();

    }

}
```
###TSPData.java

测试数据类，在这里做城市坐标数据等的输入。我直接写死在程序里了，有需要的朋友直接改动一下做一个IO就差不多了。disMap城市距离矩阵，记录各个城市间的距离。比如disMap[i][j]就是城市i和城市j之间的距离。
```
package GeneticTSP;

/**
 * TSP数据类
 * 包含：
 *         disMap 各个城市间距离矩阵
 */

public class TSPData {

    static int CITY_NUM; //城市数
    static final int SPECIES_NUM=200; //种群数
    static final int DEVELOP_NUM=1000; //进化代数
    static final float pcl=0.6f,pch=0.95f;//交叉概率
    static final float pm=0.4f;//变异概率
    static final float[][] disMap; //地图数据
    static
    {
//        int[][] cityPosition={
//                {0,0},{12,32},{5,25},{8,45},{33,17},
//                {25,7},{15,15},{15,25},{25,15},{41,12}};//10个城市（最优解:147）
//        int[][] cityPosition={
//                {60,200},{180,200},{80,180},{140,180},
//                {20,160},{100,160},{200,160},{140,140},
//                {40,120},{100,120},{180,100},{60,80},
//                {120,80},{180,60},{20,40},{100,40},
//                {200,40},{20,20},{60,20},{160,20}};//20个城市（最优解:870）
//        
        //城市坐标集合
        int[][] cityPosition={
                {1304,        2312},{3639,        1315},         
                {4177,        2244},{3712,        1399},            
                {3488,        1535},{3326,        1556},         
                {3238,        1229},{4196,        1004},         
                {4312,         790},{4386,         570},
                {3007,        1970},{2562,        1756},
                {2788,        1491},{2381,        1676},
                {1332,         695},{3715,        1678},
                {3918,        2179},{4061,        2370},
                {3780,        2212},{3676,        2578},
                {4029,        2838},{4263,        2931},
                {3429,        1908},{3507,        2367},
                {3394,        2643},{3439,        3201},
                {2935,        3240},{3140,        3550},
                {2545,        2357},{2778,        2826},
                {2370,        2975}};//31个城市（最优解:14700）

        //路径集合
        CITY_NUM=cityPosition.length;
        disMap=new float[CITY_NUM][CITY_NUM];
        for(int i=0;i<CITY_NUM;i++)
        {
            for(int j=i;j<CITY_NUM;j++)
            {
                float dis=(float)Math.sqrt(Math.pow((cityPosition[i][0] - cityPosition[j][0]),2) + Math.pow((cityPosition[i][1] - cityPosition[j][1]),2));

                disMap[i][j]=dis;
                disMap[j][i]=disMap[i][j];
            }
        }   
    }

}
```
###SpeciesIndividual.java

物种个体类，每一个个体的染色体对应着一个解决方案。下面做几点说明：

基因：这里要解决的是TSP问题，因此我们直接采用城市序列作为基因的编码。染色体由随机排列的基因组成。

物种适应度：我们说了，物种适应度是评判物种个体的好坏的一个标准。那么，对于TSP问题，解决方案的总距离越小当然就越好了。因此我们直接用了总距离的倒数作为物种适应度。那么，总距离越小，物种适应度相应就越大了。

最后再加一个打印解决方案的方法，就是把城市排列输出来。至于贪婪法生成基因，大家了解一下，这里不做介绍。
```
package GeneticTSP;

import java.util.Random;

/**
 * 个体类
 * 包含：
 *         1.createByRandomGenes 初始物种基因(随机) 基因直接用城市序列编码
 *         2.calFitness 计算物种适应度
 *         3.printRate 打印路径
 */

public class SpeciesIndividual {

    String[] genes;//基因序列
    float distance;//路程
    float fitness;//适应度
    SpeciesIndividual next;
    float rate;

    SpeciesIndividual()
    {
        //初始化
        this.genes=new String[TSPData.CITY_NUM];
        this.fitness=0.0f;
        this.distance=0.0f;
        this.next=null;
        rate=0.0f;
    }

    //初始物种基因(随机)
    void createByRandomGenes()
    {
        //初始化基因为1-CITY_NUM序列
        for(int i = 0;i < genes.length;i++)
        {
            genes[i]=Integer.toString(i+1);
        }

        //获取随机种子
        Random rand=new Random();

        for(int j=0;j<genes.length;j++)
        {
            int num= j + rand.nextInt(genes.length-j);

            //交换
            String tmp;
            tmp=genes[num];
            genes[num]=genes[j];
            genes[j]=tmp;
        }
    }

    //初始物种基因(贪婪)
    void createByGreedyGenes()
    {
        Random rand=new Random();
        int i= rand.nextInt(TSPData.CITY_NUM); //随机产生一个城市作为起点
        genes[0]=Integer.toString(i+1);
        int j;//终点
        int cityNum=0;
        do
        {
            cityNum++;

            //选出单源最短城市
            float minDis=Integer.MAX_VALUE;
            int minCity=0;
            for(j=0;j<TSPData.CITY_NUM;j++)
            {
                if(j != i)
                {
                    //判是否和已有重复
                    boolean repeat=false;
                    for(int n=0;n<cityNum;n++)
                    {
                        if(Integer.parseInt(genes[n]) == j+1)
                        {
                            repeat=true;//重了
                            break;
                        }
                    }
                    if(repeat == false)//没重
                    {
                        //判长度
                        if(TSPData.disMap[i][j] < minDis)
                        {
                            minDis=TSPData.disMap[i][j];
                            minCity=j;
                        }
                    }
                }
            }

            //加入到染色体
            genes[cityNum]=Integer.toString(minCity+1);
            i=minCity;
        }while(cityNum < TSPData.CITY_NUM-1);
    }

    //计算物种适应度
    void calFitness()
    {
        float totalDis=0.0f;
        for(int i = 0;i < TSPData.CITY_NUM;i++)
        {
            int curCity=Integer.parseInt(this.genes[i])-1;
            int nextCity=Integer.parseInt(this.genes[(i+1) % TSPData.CITY_NUM])-1;

            totalDis += TSPData.disMap[curCity][nextCity];
        }

        this.distance=totalDis;
        this.fitness=1.0f/totalDis;
    }

    //深拷贝
    public SpeciesIndividual clone()
    {   
        SpeciesIndividual species=new SpeciesIndividual();

        //复制值
        for(int i=0;i<this.genes.length;i++)
            species.genes[i]=this.genes[i];
        species.distance=this.distance;
        species.fitness=this.fitness;

        return species; 
    }

    //打印路径
    void printRate()
    {
        System.out.print("最短路线：");
        for(int i=0;i<genes.length;i++)
            System.out.print(genes[i]+"->");
        System.out.print(genes[0]+"\n");
        System.out.print("最短长度：" + distance);
    }

}
SpeciesPopulation.java

种群类，总群由物种组成。该类功能主要是把物种聚集起来形成总群的。我们姑且就当做一个物种只有一个个体。

package GeneticTSP;

/**
 * 种群类
 * 包含：
 *         1.add 添加物种
 *         2.traverse 遍历
 */

public class SpeciesPopulation {

    SpeciesIndividual head;//头结点
    int speciesNum;//物种数量

    SpeciesPopulation()
    {
        head=new SpeciesIndividual();
        speciesNum=TSPData.SPECIES_NUM;
    }

    //添加物种
    void add(SpeciesIndividual species)
    {
        SpeciesIndividual point=head;//游标
        while(point.next != null)//寻找表尾结点
            point=point.next;
        point.next=species;
    }

    //遍历
    void traverse()
    {
        SpeciesIndividual point=head.next;//游标
        while(point != null)//寻找表尾结点
        {
            for(int i=0;i<TSPData.CITY_NUM;i++)
                System.out.print(point.genes[i]+" ");
            System.out.println(point.distance);
            point=point.next;
        }
        System.out.println("_______________________");
    }

}
```
###GeneticAlgorithm.java

重头戏来了。下面重点介绍GA算法类中的几个方法：

createBeginningSpecies
创建种群，100%随机创建或者40%贪婪创建。40%贪婪创建就是40的物种采用贪婪算法生成基因。物种数由TSPData类中的物种数指定。

calRate
计算每一物种被选中的概率。物种个体中的rate变量记录了该概率。

select
轮盘制选择物种进行染色体交叉。这里的策略讲讲，我们的目标是选出优秀个体染色体交叉生成新的种群。然后再提一句，该方法只是选择个体而已，还没进行交叉操作。

1) 我们先找出最大适应度的个体。然后复制该个体到新种群去，复制数量占原来种群的1/4。

2) 然后新种群的3/4我们采用轮盘制选择，选择概率随机产生，毕竟大自然选择也是看天意的……然后每次选择那些，选中的概率（前面算出来了）大于或等于随机概率的个体，塞进新种群。注意边界处理。

crossover
交叉操作，以一定的概率区间进行。详细说明一下步骤：
1) 先随机找出两个个体（个体point和个体point.next）。
2) 在一定的概率区间。对个体point和个体point.next进行如下操作：

循环 i to city_num(i随机产生)
  找出point.genes中与point.next.genes[i]相等的位置fir
  找出point.next.genes中与point.genes[i]相等的位置sec

![](https://i.imgur.com/cK62L44.jpg)

   然后执行如下交换操作：
![](https://i.imgur.com/HCvpfOs.png)

直到结束循环

###mutate
变异操作。每一种物种都有变异的可能，我们以一定概率进行。在这个TSP问题中，我们采用的变异操作其实跟迭代搜索那个two opt有点类似。在基因序列中，随机产生i~j的区间，然后将区间反转，形成新的染色体。很easy吧……
```
package GeneticTSP;

import java.util.Random;

/**
 * 遗传算法类
 * 包含：
 *         1.run 开始跑算法
 *         2.createBeginningSpecies 创建种群
 *         3.calRate 计算每一种物种被选中的概率
 *      4.select  轮盘策略 选择适应度高的物种
 *      5.crossover 染色体交叉
 *      6.mutate 染色体变异
 *      7.getBest 获得适应度最大的物种
 */

public class GeneticAlgorithm {

        //开始遗传
        SpeciesIndividual run(SpeciesPopulation list)
        {
            //创建初始种群
            createBeginningSpecies(list);

            for(int i=1;i<=TSPData.DEVELOP_NUM;i++)
            {
                //选择
                select(list);

                //交叉
                crossover(list);

                //变异
                mutate(list);
            }   

            return getBest(list);
        }

        //创建初始种群
        void createBeginningSpecies(SpeciesPopulation list)
        {
            //100%随机
            int randomNum=(int)(TSPData.SPECIES_NUM);
            for(int i=1;i<=randomNum;i++)
            {
                SpeciesIndividual species=new SpeciesIndividual();//创建结点
                species.createByRandomGenes();//初始种群基因

                list.add(species);//添加物种
            }

//            //40%贪婪
//            int greedyNum=TSPData.SPECIES_NUM-randomNum;
//            for(int i=1;i<=greedyNum;i++)
//            {
//                SpeciesIndividual species=new SpeciesIndividual();//创建结点
//                species.createByGreedyGenes();//初始种群基因
    //
//                this.add(species);//添加物种
//            }
        }

        //计算每一物种被选中的概率
        void calRate(SpeciesPopulation list)
        {
            //计算总适应度
            float totalFitness=0.0f;
            list.speciesNum=0;
            SpeciesIndividual point=list.head.next;//游标
            while(point != null)//寻找表尾结点
            {
                point.calFitness();//计算适应度

                totalFitness += point.fitness;
                list.speciesNum++;

                point=point.next;
            }

            //计算选中概率
            point=list.head.next;//游标
            while(point != null)//寻找表尾结点
            {
                point.rate=point.fitness/totalFitness;
                point=point.next;
            }
        }

        //选择优秀物种（轮盘赌）
        void select(SpeciesPopulation list)
        {           
            //计算适应度
            calRate(list);

            //找出最大适应度物种
            float talentDis=Float.MAX_VALUE;
            SpeciesIndividual talentSpecies=null;
            SpeciesIndividual point=list.head.next;//游标

            while(point!=null)
            {
                if(talentDis > point.distance)
                {
                    talentDis=point.distance;
                    talentSpecies=point;
                }
                point=point.next;
            }

            //将最大适应度物种复制talentNum个
            SpeciesPopulation newSpeciesPopulation=new SpeciesPopulation();
            int talentNum=(int)(list.speciesNum/4);
            for(int i=1;i<=talentNum;i++)
            {
                //复制物种至新表
                SpeciesIndividual newSpecies=talentSpecies.clone();
                newSpeciesPopulation.add(newSpecies);
            }

            //轮盘赌list.speciesNum-talentNum次
            int roundNum=list.speciesNum-talentNum;
            for(int i=1;i<=roundNum;i++)
            {
                //产生0-1的概率
                float rate=(float)Math.random();

                SpeciesIndividual oldPoint=list.head.next;//游标
                while(oldPoint != null && oldPoint != talentSpecies)//寻找表尾结点
                {
                    if(rate <= oldPoint.rate)
                    {
                        SpeciesIndividual newSpecies=oldPoint.clone();
                        newSpeciesPopulation.add(newSpecies);

                        break;
                    }
                    else
                    {
                        rate=rate-oldPoint.rate;
                    }
                    oldPoint=oldPoint.next;
                }
                if(oldPoint == null || oldPoint == talentSpecies)
                {
                    //复制最后一个
                    point=list.head;//游标
                    while(point.next != null)//寻找表尾结点
                        point=point.next;
                    SpeciesIndividual newSpecies=point.clone();
                    newSpeciesPopulation.add(newSpecies);
                }

            }
            list.head=newSpeciesPopulation.head;
        }

        //交叉操作
        void crossover(SpeciesPopulation list)
        {
            //以概率pcl~pch进行
            float rate=(float)Math.random();
            if(rate > TSPData.pcl && rate < TSPData.pch)
            {           
                SpeciesIndividual point=list.head.next;//游标
                Random rand=new Random();
                int find=rand.nextInt(list.speciesNum);
                while(point != null && find != 0)//寻找表尾结点
                {
                    point=point.next;
                    find--;
                }

                if(point.next != null)
                {
                    int begin=rand.nextInt(TSPData.CITY_NUM);

                    //取point和point.next进行交叉，形成新的两个染色体
                    for(int i=begin;i<TSPData.CITY_NUM;i++)
                    {
                        //找出point.genes中与point.next.genes[i]相等的位置fir
                        //找出point.next.genes中与point.genes[i]相等的位置sec
                        int fir,sec;
                        for(fir=0;!point.genes[fir].equals(point.next.genes[i]);fir++);
                        for(sec=0;!point.next.genes[sec].equals(point.genes[i]);sec++);
                        //两个基因互换
                        String tmp;
                        tmp=point.genes[i];
                        point.genes[i]=point.next.genes[i];
                        point.next.genes[i]=tmp;

                        //消去互换后重复的那个基因
                        point.genes[fir]=point.next.genes[i];
                        point.next.genes[sec]=point.genes[i];

                    }
                }
            }
        }

        //变异操作
        void mutate(SpeciesPopulation list)
        {   
            //每一物种均有变异的机会,以概率pm进行
            SpeciesIndividual point=list.head.next;
            while(point != null)
            {
                float rate=(float)Math.random();
                if(rate < TSPData.pm)
                {
                    //寻找逆转左右端点
                    Random rand=new Random();
                    int left=rand.nextInt(TSPData.CITY_NUM);
                    int right=rand.nextInt(TSPData.CITY_NUM);
                    if(left > right)
                    {
                        int tmp;
                        tmp=left;
                        left=right;
                        right=tmp;
                    }

                    //逆转left-right下标元素
                    while(left < right)
                    {
                        String tmp;
                        tmp=point.genes[left];
                        point.genes[left]=point.genes[right];
                        point.genes[right]=tmp;

                        left++;
                        right--;
                    }
                }
                point=point.next;
            }
        }

        //获得适应度最大的物种
        SpeciesIndividual getBest(SpeciesPopulation list)
        {
            float distance=Float.MAX_VALUE;
            SpeciesIndividual bestSpecies=null;
            SpeciesIndividual point=list.head.next;//游标
            while(point != null)//寻找表尾结点
            {
                if(distance > point.distance)
                {
                    bestSpecies=point;
                    distance=point.distance;
                }

                point=point.next;
            }

            return bestSpecies;
        }

}
```
以上就是遗传算法的java代码。




运行结果：



10个城市（最优解:147）
![](https://i.imgur.com/xez5ezn.png)



20个城市（最优解:870）
![](https://i.imgur.com/C1aQgh5.png)



31个城市（最优解:14700）
![](https://i.imgur.com/EfQqY29.png)

最后在多说一句，这代码跑不出最优解也正常。启发式算法求近似解还是得靠人品的胸弟。跑不出最优解那只能说明……小编太帅吓到编译器了而已。嗯，一定是这样的。


![](https://i.imgur.com/mtSHD9G.jpg)



-The End-
文案 / 邓发珩（大一）
排版 / 邓发珩（大一）
代码 / 邓发珩（大一）
审核 / 贺兴（大三）
指导老师 / 秦时明岳
