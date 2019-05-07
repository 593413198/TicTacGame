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
	ShowBoard();
	int winner = CheckResult();
	Turn = (depth%2==0) ? -1:1;
	if (depth==9 || winner){
		return 1; //9回合到，棋盘落满，游戏结束
	}
	/* TODO 赋予初步智能：堵危险二子 */
	int ans = Check4();
	/*
	if (ans==2) { //己方2子
		ChessBoard[Dx][Dy] = Turn; //填子获胜
		Go(depth+1);
		ChessBoard[Dx][Dy] = Turn;
		cout << Name[Turn+1] << "获胜" << endl;
		return 0;
	}
	if (ans==1) { //对方2子
		ChessBoard[Dx][Dy] = Turn; //封堵对手2子
		Go(depth+1);
		ChessBoard[Dx][Dy] = 0;
		return 0;
	}
	*/
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			Turn = (depth%2==0) ? -1:1;
			if (!ans && ChessBoard[i][j]==0){ //找到空位置就落子
				ChessBoard[i][j] = Turn;
				Go(depth+1);
				ChessBoard[i][j] = 0;
			}
			if (ans && Dx==i && Dy==j) { //己方2子 或 对方2子
				ChessBoard[i][j] = Turn;
				Go(depth+1);
				ChessBoard[i][j] = 0;
				return 1;
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
	Turn = (NowTurn%2==0)?-1:1; //轮到谁落子 	
	cout << "当前轮到" << Name[WhoTurn+1] << "落子" << endl;
	/* 回溯，寻找有没有'O'获胜的子节点 */
	CanWin = false;
	//Go(NowTurn);	
	int ans = Check4();
	if (ans)
		cout << "要堵住的位置:" <<Dx+1 << Dy+1 << endl;
	else
		cout << "不用封堵"<<endl;
	return 1;
}

int main(){
	/*
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			ChessBoard[i][j] = 0; 
	*/
	//Input();
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			cin >> ChessBoard[i][j];
	NowTurn = Sum(); //回合数
	Turn = (NowTurn%2==0)?-1:1; //轮到谁落子 	
	cout << "轮到落子:" << Name[Turn+1] << endl;
	Go(NowTurn);
	return 1;
}

