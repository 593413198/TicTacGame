#include "ChessBoard.h"

int Round = 0; //第0回合-未开始
int Turn = -1; //"O"先落子
int ChessBoard[3][3] = {{0,0,0},{0,0,0},{0,0,0}}; //棋盘初始状态，无子


/* TODO 函数的实现  */
void Run()
{	
	Round ++; //回合数加1
	Turn  = 1 - Turn; //更换落子方
}

bool check1(int i, int j)
{	/* return 1: 水平方向连成三子
	   return 0: else */
	if (ChessBoard[i][(j+1)%3] + ChessBoard[i][(j+2)%3] == 2 * ChessBoard[i][j] ) 
		return 1;
	return 0;
}

bool check2(int i, int j)
{
	if (ChessBoard[(i+1)%3][j] + ChessBoard[(i+2)%3][j] == 2 * ChessBoard[i][j] )
	   	return 1;
	return 0;
}

bool check3(int i, int j)
{
	if (ChessBoard[(i+1)%3][(j+1)%3] + ChessBoard[(i+2)%3][(j+2)%3] == 2 * ChessBoard[i][j] ) 
		return 1;
	return 0;
}

int CheckResult()
{	/* 不会出现双方同时连成三子的情况；
	   return  0: 胜负未分
	   return -1: O获胜
	   return  1: X获胜 */
	int chess; //当前位置的棋子类型
	int ans;   //结果
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			chess = ChessBoard[i][j];
			ans  = check1(i,j);	
			if (ans) return chess;
			ans = check2(i,j);
			if (ans) return chess;
			ans = check3(i,j);
			if (ans) return chess;
		}
	}
	return 0;
}

