
号外！号外！常年用 TSP 举例的某干货分享板块终于 倒闭 改革了！小编终于被boss揪去关·禁·闭、学·习·进·阶、突·破·自·我了！


![](https://i.imgur.com/a7G9Eqk.jpg)

本着 独学学 不如 装装× 分享分享 的想法，下面来介绍下最近陪伴小编入眠的VRPTW——带时间窗车辆路径规划问题。
惯例奉上小编的 素质三连 攻略三连 帮你十分钟快速搞懂 VRPTW 讲什么、什么样、怎么解，帮助你从零开始快速入门！

![](https://i.imgur.com/S0n40Xo.jpg)

＊


内容提要：
####1.什么是VRPTW
####2.CPLEX求解VRPTW实例
####3.CPLEX操作补充说明

##1.什么是VRPTW
   提到带时间窗车辆路径问题（vehicle routing problems with time windows，VRPTW），就不得不先说说车辆路径问题（VRP）。

什么是VRP？

 车辆路径问题（VRP）最早是由 Dantzig 和 Ramser 于1959年首次提出，它是指一定数量的客户，各自有不同数量的货物需求，配送中心向客户提供货物，由一个车队负责分送货物，组织适当的行车路线，目标是使得客户的需求得到满足，并能在一定的约束下，达到诸如路程最短、成本最小、耗费时间最少等目的。

VRP图示 

![](https://i.imgur.com/RTkN6eB.jpg)

##什么是VRPTW？
由于VRP问题的持续发展，考虑需求点对于车辆到达的时间有所要求之下，在车辆途程问题之中加入时窗的限制，便成为带时间窗车辆路径问题（VRP with Time Windows, VRPTW）。带时间窗车辆路径问题（VRPTW）是在VRP上加上了客户的被访问的时间窗约束。在VRPTW问题中，除了行驶成本之外, 成本函数还要包括由于早到某个客户而引起的等待时间和客户需要的服务时间。
在VRPTW中，车辆除了要满足VRP问题的限制之外，还必须要满足需求点的时窗限制，而需求点的时窗限制可以分为两种，一种是硬时窗（Hard Time Window），硬时窗要求车辆必须要在时窗内到达，早到必须等待，而迟到则拒收；另一种是软时窗（Soft Time Window），不一定要在时窗内到达，但是在时窗之外到达必须要处罚，以处罚替代等待与拒收是软时窗与硬时窗最大的不同。

##2.CPLEX求解VRPTW实例
   解决带时间窗车辆路径问题（vehicle routing problems with time windows，VRPTW）的常用求解方法：
1.精确解算法（Exact methods）

精确解算法解VRPTW问题主要有三个策略，拉格朗日松弛、列生成和动态规划，但是可以求解的算例规模非常小。

2.途程构建启发式算法（Route-building heuristics）

在问题中以某节点选择原则或是路线安排原则，将需求点一一纳入途程路线的解法。

3.途程改善启发式算法（Route-improving heuristics）

先决定一个可行途程，也就是一个起始解，之后对这个起始解一直做改善，直到不能改善为止。

4.通用启发式算法（Metaheuristics）

传统区域搜寻方法的最佳解常因起始解的特性或搜寻方法的限制，而只能获得局部最佳解，为了改善此一缺点，近年来在此领域有重大发展，是新一代的启发式解法，包含禁忌搜索算法（Tabu Search）、模拟退火法（Simulated Annealing）、遗传算法（Genetic Algorithm）和门坎接受法（Threshold Accepting）等，可以有效解决陷入局部最优的困扰。


##VRPTW问题建模实例
![](https://i.imgur.com/s66kkpf.jpg)

![](https://i.imgur.com/HqIvYEv.jpg)

![](https://i.imgur.com/DNRtf96.jpg)
  接下来分享一波代码和算例  ↓ ↓ ↓
###代码（java版本-用cplex求解）


![](https://i.imgur.com/1haAc0z.jpg)





算例演示（Solomon标准算例）
算例一    
输入文件格式为：

![](https://i.imgur.com/cQRwnX6.jpg)

![](https://i.imgur.com/PTpAGo5.jpg)

![](https://i.imgur.com/NqTGpXM.jpg)

输出结果为：
result
routes=
[[0, 101]
[0, 5, 3, 7, 8, 10, 11, 9, 6, 4, 2, 1, 75, 101]
[0, 98, 96, 95, 94, 92, 93, 97, 100, 99, 101]
[0, 43, 42, 41, 40, 44, 46, 45, 48, 51, 50, 52, 49, 47, 101]
[0, 81, 78, 76, 71, 70, 73, 77, 79, 80, 101]
[0, 90, 87, 86, 83, 82, 84, 85, 88, 89, 91, 101]
[0, 101]
[0, 32, 33, 31, 35, 37, 38, 39, 36, 34, 101]
[0, 20, 24, 25, 27, 29, 30, 28, 26, 23, 22, 21, 101]
[0, 57, 55, 54, 53, 56, 58, 60, 59, 101]
[0, 67, 65, 63, 62, 74, 72, 61, 64, 68, 66, 69, 101]
[0, 13, 17, 18, 19, 15, 16, 14, 12, 101]]

cplex_time 157.077920593s bestcost 827.3

算例二    
输入文件格式为：
![](https://i.imgur.com/ApWjY8E.jpg)

![](https://i.imgur.com/qc5w4O6.jpg)

![](https://i.imgur.com/pCgsCu9.jpg)



输出结果为：
result
routes=
[[0, 101]
[0, 5, 3, 7, 8, 10, 11, 9, 6, 4, 2, 1, 75, 101]
[0, 98, 96, 95, 94, 92, 93, 97, 100, 99, 101]
[0, 43, 42, 41, 40, 44, 46, 45, 48, 51, 50, 52, 49, 47, 101]
[0, 81, 78, 76, 71, 70, 73, 77, 79, 80, 101]
[0, 90, 87, 86, 83, 82, 84, 85, 88, 89, 91, 101]
[0, 101]
[0, 32, 33, 31, 35, 37, 38, 39, 36, 34, 101]
[0, 20, 24, 25, 27, 29, 30, 28, 26, 23, 22, 21, 101]
[0, 57, 55, 54, 53, 56, 58, 60, 59, 101]
[0, 67, 65, 63, 62, 74, 72, 61, 64, 68, 66, 69, 101]
[0, 13, 17, 18, 19, 15, 16, 14, 12, 101]]

cplex_time 142.142142417s bestcost 827.3
上述代码仅供分享交流学习用，如有需要复制下面链接自取 ↓ ↓ ↓
http://paste.ubuntu.com/25476905/
或直接戳文章底部的 阅读原文，跳转代码页面！

##3.CPLEX操作补充说明
关于上述java代码中调用的cplex，特在此附上cplex安装说明：

1
软件下载及安装

Cplex64位版本下载地址可移步 微信公众号数据魔术师获取百度云网盘链接~~


![](https://i.imgur.com/ixy9yC4.png)
下载完直接如下图点击安装即可~

![](https://i.imgur.com/2Iitqe1.png)

2
小编这里是在Eclipse中使用Java调用Cplex，所以需要在Eclipse中配置Cplex调用环境。

需求文件地址：
cplex.jar(在…\IBM\ILOG\CPLEX_Studio1263\cplex\lib目录下找到)
cplex1263.dll(在…\IBM\ILOG\CPLEX_Studio1263\cplex\bin\x64_win64目录下找到)。

1. 将cplex.jar加到工程的Build Path中：
 在工程中点击鼠标右键，
Build Path->Configure Build Path



![](https://i.imgur.com/uSlmOu1.jpg)


2. cplex1263.dll可以设置到运行时的环境中（VM arguments），或者添加到项目的Native library location（这里小编选用的是第二种）： ![](https://i.imgur.com/Ecbrf27.jpg)

![](https://i.imgur.com/uvdCZk2.jpg)





   相信现在大家对VRPTW的相关内容更加了解了！
   如果大家对 VRPTW 及 文中所叙内容 还有疑问或想要交流心得建议，欢迎移步留言区！
   最后再来一发安利——如果你是初学算法，或者是喜欢交流算法的master，再或者仅仅是想要了解算法是什么...欢迎关注我们的公众号和我们一起交流！学习！进步！
![](https://i.imgur.com/2Dfd6m1.jpg)

—end—     
编辑：谢良桢（1922193128@qq.com                 
黄楠：（huangnanhust.163.com）      
代码：黄楠（huangnanhust.163.com）      
指导老师：秦时明岳（professor.qin@qq.com）