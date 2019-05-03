#include "ChessBoard.h"
int Round = 0; //第0回合-未开始
int Turn = -1; //"O"先落子
int ChessBoard[3][3] = {{0,0,0},{0,0,0},{0,0,0}}; //棋盘初始状态，无子
char Graph[3][3]; //图形界面

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
	if (i==j){ 
		if (ChessBoard[(i+1)%3][(j+1)%3] + ChessBoard[(i+2)%3][(j+2)%3] == 2 * ChessBoard[i][j] ) 
			return 1;
	}
	if (i+j==2){
		if (ChessBoard[(i+1)%3][(j-1)%3] + ChessBoard[(i+2)%3][(j-2)%3] == 2 * ChessBoard[i][j] ) 
			return 1;
	}
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
			if (chess){
				ans  = check1(i,j);	
				if (ans) {
					return chess;
				}
				ans = check2(i,j);
				if (ans) {
					return chess;
				}
				ans = check3(i,j);
				if (ans && (i==j||i+j==2)) {
					return chess;
				}
			}
		}
	}
	return 0;
}


void ShowBoard(){
	//打印出棋盘的图形化界面
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (ChessBoard[i][j]==0) Graph[i][j] = ' ';
			else if (ChessBoard[i][j]==-1) Graph[i][j] = 'O';
			else Graph[i][j] = 'X';
		}
	}
	cout << "+---+---+---+" << endl;
	cout << "| " << Graph[0][0] << " | " << Graph[0][1] << " | " << Graph[0][2] << " |" << endl;
	cout << "|---|---|---|" << endl;
	cout << "| " << Graph[1][0] << " | " << Graph[1][1] << " | " << Graph[1][2] << " |" << endl;
	cout << "|---|---|---|" << endl;
	cout << "| " << Graph[2][0] << " | " << Graph[2][1] << " | " << Graph[2][2] << " |" << endl;
	cout << "+---+---+---+" << endl;
}
