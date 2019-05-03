#include "PlayGame.h"
#include <stdio.h>
int ans = 0; //所有局面数量
int times[3] = {0,0,0}; //先手胜平负的局数统计
char Name[3] = {'O',' ','X'};
int NowTurn; //当前回合数
int WhoTurn; //记录当前局面轮到谁落子 
bool CanWin; //寻找是否有最终获胜的子节点

int Go(int depth){
	/* 表示进行到第depth回合
	 * depth%2=0: turn=-1 
	 * depth%2=1: turn=1  */
	if (depth==9){
		//ans ++;
		//times[1]++;
		return 1; //9回合到，棋盘落满，游戏结束
	}
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (ChessBoard[i][j]==0){ //找到空位置就落子
				if (depth%2 == 0) Turn = -1; //确定当前轮到谁落子
				else Turn = 1;
				ChessBoard[i][j] = Turn;
				int winner = CheckResult();
				if (!winner) //若未分出胜负，继续下一回合
					Go(depth+1);
				else{ //已分出胜负，不必继续搜索，回溯
					//ShowBoard();
					//times[winner+1] ++;
					//ans ++;
					if (winner == WhoTurn){
						cout << "其中一个获胜局面是:"<<endl;
						ShowBoard();
						CanWin = true;
						return 0;
					}
					ChessBoard[i][j] = 0;
					return 0;
				}
				ChessBoard[i][j] = 0;
			}
		}
	}
}

int Sum(){
	int NumChess=0;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			if (ChessBoard[i][j])
				NumChess++;
	return NumChess;
}

bool Input(){

	cout << "(测试专用)，请输入当前局面："<<endl;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			cin >> ChessBoard[i][j];
	ShowBoard();
	NowTurn = Sum(); //回合数
	WhoTurn = (NowTurn%2==0)?-1:1; //轮到谁落子 	
	cout << "当前轮到" << Name[WhoTurn+1] << "落子" << endl;
	/* 回溯，寻找有没有'O'获胜的子节点 */
	CanWin = false;
	Go(NowTurn);	
	return 1;
}

int main(){
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			ChessBoard[i][j] = 0;
	Input();
	if (CanWin)
	   cout << "此人可以赢" <<endl;
	else
		cout << "此人不可能赢" <<endl;	
	return 1;
}

