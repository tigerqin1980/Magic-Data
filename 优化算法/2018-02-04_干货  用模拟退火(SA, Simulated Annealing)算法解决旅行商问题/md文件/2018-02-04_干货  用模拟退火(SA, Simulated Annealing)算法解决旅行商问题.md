

# 01 What is 旅行商问题(TSP)?
>TSP问题（Traveling Salesman Problem，旅行商问题），由威廉哈密顿爵士和英国数学家克克曼T.P.Kirkman于19世纪初提出。问题描述如下： 
**有若干个城市，任何两个城市之间的距离都是确定的，现要求一旅行商从某城市出发必须经过每一个城市且只在一个城市逗留一次，最后回到出发的城市，问如何事先确定一条最短的线路已保证其旅行的费用最少？**

如下图所示：
![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1517671205242&di=22e4df5b89baf9c9e3056a26c11fb3f2&imgtype=0&src=http%3A%2F%2Fs16.sinaimg.cn%2Fmw690%2F0027mV13gy6GskPnbc30f)

# 02 模拟退火算法（Simulate Annealing Arithmetic，SAA）
## 2.1 什么是模拟退火算法(简介)?
模拟退火算法（Simulate Anneal Arithmetic，SAA）是一种通用概率演算法，用来在一个大的搜寻空间内找寻命题的最优解。它是基于Monte-Carlo迭代求解策略的一种随机寻优算法。
模拟退火算法是S.Kirkpatrick, C.D.Gelatt和M.P.Vecchi等人在1983年发明的，1985年，V.Černý也独立发明了此演算法。模拟退火算法是解决TSP问题的有效方法之一。
## 2.2 模拟退火算法的来源
模拟退火算法来源于固体退火原理。
物理退火: 将材料加热后再经特定速率冷却，目的是增大晶粒的体积，并且减少晶格中的缺陷。材料中的原子原来会停留在使内能有局部最小值的位置，加热使能量变大，原子会离开原来位置，而随机在其他位置中移动。退火冷却时速度较慢，使得原子有较多可能可以找到内能比原先更低的位置。
模拟退火: 其原理也和固体退火的原理近似。模拟退火算法从某一较高初温出发，伴随温度参数的不断下降,结合概率突跳特性在解空间中随机寻找目标函数的全局最优解，即在局部最优解能概率性地跳出并最终趋于全局最优。
## 2.3 模拟退火算法思想
在介绍模拟退火算法之前，有必要给大家科普一下爬山算法 (Hill Climbing)。
### 2.3.1 爬山算法
爬山算法是一种简单的贪心搜索算法，该算法每次从当前解的临近解空间中选择一个最优解作为当前解，直到达到一个局部最优解。这种算法思想很单纯，但是也存在一个很大的缺陷。在搜索选择的过程中有可能会陷入局部最优解，而这个局部最优解不一定是全局最优解。比如下面这个问题：
![图1](http://oyxhmjutw.bkt.clouddn.com/18-2-3/31215751.jpg)
假设A是当前解，爬山算法往前继续搜索，当搜索到B这个局部最优解时就会停止搜索了。因为此时在B点无论是往哪边走都不会得到更优的解了。但是，聪明的同学已经发现了，全局最优解在C点。
### 2.3.2 模拟退火算法
爬山法是完完全全的贪心法，这种贪心是很鼠目寸光的，只把眼光放在局部最优解上，因此只能搜索到局部的最优值。模拟退火其实也是一种贪心算法，只不过与爬山法不同的是，模拟退火算法在搜索过程引入了随机因素。模拟退火算法以一定的概率来接受一个比当前解要差的解，因此有可能会跳出这个局部的最优解，达到全局的最优解。从上图来说，模拟退火算法在搜索到局部最优解B后，会以一定的概率接受向右的移动。也许经过几次这样的不是局部最优的移动后会到达BC之间的峰点D，这样一来便跳出了局部最优解B，继续往右移动就有可能获得全局最优解C。如下图：
![](http://oyxhmjutw.bkt.clouddn.com/18-2-3/32004749.jpg)

关于普通Greedy算法与模拟退火，这里也有一个有趣的比喻：
普通Greedy算法：兔子朝着比现在低的地方跳去。它找到了不远处的最低的山谷。但是这座山谷不一定最低的。

模拟退火：兔子喝醉了。它随机地跳了很长时间。这期间，它可能走向低处，也可能踏入平地。但是，它渐渐清醒了并朝最低的方向跳去。

如此一来，大家对模拟退火算法有了一定的认识，但是这还是不够的。对比上面两种算法，对于模拟退火算法我们提到了一个很important的概念--一定的概率，关于这个一定的概率是如何计算的。这里还是参考了固体的物理退火过程。(高能预警:下面的介绍可能有那么一点点难懂，但是耐心仔细看是不成问题的。大家坚持一下哈！)

根据热力学的原理，在温度为T时，出现能量差为dE的降温的概率为P(dE)，表示为：
>P(dE) = exp( dE/(kT) )

其中k是一个常数，exp表示自然指数，且dE<0(温度总是降低的)。这条公式指明了：
1) 温度越高，出现一次能量差为dE的降温的概率就越大；
2) 温度越低，则出现降温的概率就越小。又由于dE总是小于0（不然怎么叫退火），因此dE/kT < 0 ，exp(dE/kT)取值是(0,1),那么P(dE)的函数取值范围是(0,1) 。

随着温度T的降低，P(dE)会逐渐降低。我们将一次向较差解的移动看做一次温度跳变过程，我们以概率P(dE)来接受这样的移动。也就是说，在用固体退火模拟组合优化问题，将内能E模拟为目标函数值 f，温度T演化成控制参数 t，即得到解组合优化问题的模拟退火演算法：由初始解 i 和控制参数初值 t 开始，对当前解重复“产生新解→计算目标函数差→接受或丢弃”的迭代，并逐步衰减 t 值，算法终止时的当前解即为所得近似最优解。

因此我们归结起来就是以下几点：
1) 若f( Y(i+1) ) <= f( Y(i) )  (即移动后得到更优解)，则总是接受该移动；
2) 若f( Y(i+1) ) > f( Y(i) )  (即移动后的解比当前解要差)，则以一定的概率接受移动，而且这个概率随着时间推移逐渐降低（逐渐降低才能趋向稳定）相当于上图中，从B移向BC之间的小波峰D时，每次右移(即接受一个更糟糕值)的概率在逐渐降低。如果这个坡特别长，那么很有可能最终我们并不会翻过这个坡。如果它不太长，这很有可能会翻过它，这取决于衰减 t 值的设定。
## 2.4 模拟退火算法伪代码
相信通过上面的讲解，大家已经对模拟退火算法认识得差不多了。下面我们来看看它的伪代码是怎么实现的。
![](http://oyxhmjutw.bkt.clouddn.com/18-2-3/45009273.jpg)

# 03 使用模拟退火算法解决旅行商问题
旅行商问题属于所谓的NP完全问题。精确的解决TSP只能通过穷举所有的路径组合，其时间复杂度是O(N!) 。而使用模拟退火算法则可以较快速算法一条近似的最优路径。大体的思路如下：
1. 产生一条新的遍历路径P(i+1)，计算路径P(i+1)的长度L( P(i+1) )
2. 若L(P(i+1)) < L(P(i))，则接受P(i+1)为新的路径，否则以模拟退火的那个概率接受P(i+1) ，然后降温
3. 重复步骤1，2直到满足退出条件

好了多说无益，下面大家一起看代码吧。
![](http://oyxhmjutw.bkt.clouddn.com/18-2-3/69566552.jpg)

代码运行结果：
![](http://oyxhmjutw.bkt.clouddn.com/18-2-3/89748202.jpg)

代码下载：https://pan.baidu.com/s/1bqMjoE7

# 04 小结
从上面的过程我们可以看出，模拟退火算法是一种随机算法，它有一定的概率能求得全局最优解，但不一定。用模拟退火算法可以较快速地找出问题的最优近似解。它的关键之处还是在于允许一定的差解。不过，在小编不成熟的眼光看来，人生亦有相似之处。有时候可能放弃眼前短浅的利益，最终才可能获得更好的未来。现在失去的，在未来会以另一种方式归来。