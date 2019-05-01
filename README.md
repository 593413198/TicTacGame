## 井字棋AI的实现
**开始时间：**
`2019/4/29`

**搭建环境：**   
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

**思路分析：**
```c
1. 暴力穷举所有局面，共有9！种可能，即362880种；
2. 考虑有些局面中途就产生输赢，不用继续搜索因此剪枝，解空间缩小为100128种，先手胜平负的概率分别是47%,25%,28%，因此理论上先手占优；(通过代码遍历得出)
3. 通过对称性可以进一步缩小解空间，此处省略；
4. 回溯法核心伪代码：
Go(depth){
	if (depth==9)
		return;
	do 找到空位置(i,j)并落子;
	if (胜负已分)
		Go(depth+1);
	do 将(i,j)上的落子还原;
}
```
