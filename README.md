## 井字棋AI的实现
**开始时间：**
`2019/4/29`

**搭建环境：**
`Ubuntu 18.04  gcc 7.3.0`

**游戏规则：**
```
+---+---+---+    +---+---+---+
|   |   |   |    | O |   | X | 
|---|---|---|    |---|---|---|
|   |   |   |    | O | O | X |
|---|---|---|    |---|---|---|
|   |   |   |    | O | X |   | 
+---+---+---+    +---+---+---+
如图3*3的棋盘，先手落"O"，后手落"X"；若横、竖、斜方向出现三子连线，则胜出；
如右图，先手方"O"胜出:
```

## 思路分析：
**1.0 代码架构（已实现部分）**
```c
#ChessBoard.h  
ChessBoard.cpp
//棋盘的存储、判定输赢、可视化打印、局面评估函数

#PlayGame.h  
PlayGame.cpp
//模拟对弈、遍历回溯所有局面

example.c  /* 输入棋盘的测试数据 */
result.c   /* 输出可视化结果     */
Makefile   /* make编译           */
```

**1.1 先回溯遍历所有情形，摸个底**
```c
1. 暴力穷举所有局面，共有9!种可能，即362880种；
2. 考虑到产生输赢游戏就结束，有些局面不用继续搜索下去，解空间缩小为113416种，先手胜平负的局面占比分别是49%,23%,28%，因此理论上先手占优；(通过代码遍历得出,尽管实际中这种数据没任何意义)
3. 通过对称性可以进一步缩小解空间，此处省略；
4. 回溯法核心伪代码：
Go(depth){
	if (depth==9)
		return;
	do 找到空位置(i,j)并落子;
	if (胜负未分)
		Go(depth+1);
	do 将(i,j)上的落子还原;
}
```

**1.2 可视化打印棋盘，方便检查局面**
```c
#include "ChessBoard.h"
void ShowBoard(); //可视化打印
char Graph[3][3]; //空则为' '，先手'O'，后手'X'
//通过规范化的输出实现棋盘
```

**1.3 尝试模拟博弈: 对于任一种局面，判断是否存在最终获胜的子节点**
>以下全部建立在，所有局面都可能且必然会出现，即博弈双方零智能的情况下
```c
#include "PlayGame.h"
//给一个输入接口，用来检测判断的正确性
int WhoTurn;  //当前落子方
bool CanWin;  //落子方能否赢
int Sum();    //返回输入局面的落子数，即回合数
bool Input(); //输入一个局面，判断当前落子方是否有赢的可能
```

**1.4 赋予一些初步智能：如遇己方二子必填、遇对方二子必堵**
```c
如以下局面其实只有唯一解:
+---+---+---+    +---+---+---+
| O | X |   |    | O | X | O | 
|---|---|---|    |---|---|---|
|   | X | O |    | O | X | O |
|---|---|---|    |---|---|---|
| X | O |   |    | X | O | X | 
+---+---+---+    +---+---+---+
左图为输入局面；右图为结果局面；
唯一流程：O必落右上角封堵，接着X落右下角封堵，最后O落子棋盘下满；

#include "ChessBoard.h"
int Check4(); //return 2:己方2子   return 1:对方2子
//修改Go()：优先填己方2子，其次堵对方2子，最后才是遍历for循环
```

**阶段1.5 设计局面评估函数：对每个位置给出相应价值，每次挑价值最高的落子**

- 一个3*3的棋盘能同时覆盖3个点位的共有8条线，横3条，竖3条，斜2条；以此作为评分的依据； 
	- 评估规则1：每有一条线经过，该点位价值+1
	- 评估规则2：每有一个己方棋子同线，且无对方障碍子，该点位价值再+1
	- 评估规则3：若有一个对方棋子同线，该点价值不受影响
	- 评估规则4：各种局面处理优先级: 己方2子 > 对方2子 > 选择价值最大点位落子
```c
下图：对于空棋盘先手方O的每个点位价值如下
(因为中心点有4条线经过，所有该点位价值为4)
因此先手O最佳开局位置是中心点
+---+---+---+ 
| 3 | 2 | 3 |
|---|---|---| 
| 2 | 4 | 2 | 
|---|---|---| 
| 3 | 2 | 3 |
+---+---+---+

对于左图的局面，轮到先手方O落子，相应的价值分布如右图
按照评估规则2，只有左下角的点位不加分；
所以先手方O合理的落子位置是左上角或右下角(两个点位等价)
+---+---+---+
|   |   | X |
|---|---|---|
|   | O |   |
|---|---|---|
|   |   |   |
+---+---+---+ 

先根据规则1打分
+---+---+---+
| 3 | 2 | X |
|---|---|---|
| 2 | O | 2 |
|---|---|---| 
| 3 | 2 | 3 | 
+---+---+---+ 

再根据规则2打分
+---+---+---+
| 4 | 3 | X |
|---|---|---|
| 3 | O | 3 |
|---|---|---|
| 3 | 3 | 4 | 
+---+---+---+
```
 - 实现函数如下
```c
#include <ChessBoard.h>
int Value[3][3]; //记录每个点位的价值
void ShowValue; //打印点位价值图
void Evaluate(); //点位的价值评估函数
```
