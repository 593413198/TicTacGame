#include "Generator.h"
int tmp_i,tmp_j;
int Mark[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int Depth = 1;

void InitMark(){
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			Mark[i][j] = 0;
}

int GoStep(int Turn){
	/* 若chess=1，找到所有为0的位置，赋值1即可 
	 * return 1: 走完一步
	 * return 0: 棋盘已满 */
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (!ChessBoard[i][j] && Mark[i][j]!=Depth){ 
				//避免重复回溯造成死循环
				ChessBoard[i][j] =  Turn;
				tmp_i = i;
				tmp_j = j;
				Mark[i][j] = Depth;
				return 1;
			}
		}
	}	
	return 0;
}

int Go(int depth){
	Depth = depth;
	/* Go()调用一次，即进行一个回合 
	 * depth%2=0: turn=-1 
	 * depth%2=1: turn=1  */
	//cout << "Now for: " << Turn << endl;
	if (depth%2==1) Turn=-1;
	else Turn=1;
	if ( !GoStep(Turn) ) {//棋盘走满
		cout << "++++" <<endl;
		show();
		int ans = CheckResult();
		cout << "Winner is: " << ans << endl;
		cout << "++++" <<endl;
		return ans; //返回胜负情况
	}
	show();
	Go(depth+1);
	ChessBoard[tmp_i][tmp_j] = 0; //回溯并且标记
	Go(depth);
}
