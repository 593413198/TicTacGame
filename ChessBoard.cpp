#include "ChessBoard.h"
int Round = 0; //第0回合-未开始
int Turn = -1; //"O"先落子
int ChessBoard[3][3] = {{0,0,0},{0,0,0},{0,0,0}}; //棋盘初始状态，无子
char Graph[3][3]; //图形界面
int Dx=-1,Dy=-1;

int Check1(int i, int j)
{	/* return 3: 己方2子(必填)
	   return 2: 对方2子（必堵）
	   return 1: 出现3子
	   return 0: else */
	int sum = ChessBoard[i][(j+1)%3] + ChessBoard[i][(j+2)%3]; //其余两子和
	int x = ChessBoard[i][j];
	if (sum == 2 * x ) return 1;
	if (x==0 && sum == 2*Turn) return 3;
	if (x==0 && sum == -2*Turn) return 2;
	return 0;
}

int Check2(int i, int j)
{	// 竖直方向
	int sum = ChessBoard[(i+1)%3][j] + ChessBoard[(i+2)%3][j]; //其余两子和
	int x = ChessBoard[i][j];
	if (sum == 2 * x ) return 1;
	if (x==0 && sum == 2*Turn) return 3;
	if (x==0 && sum == -2*Turn) return 2;
	return 0;
}

int Check3(int i, int j)
{   // 左上到右下
	int sum1=ChessBoard[(i+1)%3][(j+1)%3]+ChessBoard[(i+2)%3][(j+2)%3]; 
	// 左下到右上
	int sum2=ChessBoard[(i+1)%3][(j+2)%3]+ChessBoard[(i+2)%3][(j+1)%3]; 
	int x = ChessBoard[i][j];
	if (i==j){ 
		if (sum1 == 2 * x) return 1;
		if (x==0 && sum1 == 2*Turn)  return 3;
		if (x==0 && sum1 == -2*Turn) return 2;
	}
	if (i+j==2){
		if (sum2 == 2 * x) return 1;
		if (x==0 && sum2 == 2*Turn)  return 3;
		if (x==0 && sum2 == -2*Turn) return 2;
	}
	return 0;
}

int Check4()
{	/* 检测己方和对方是否出现2子；优先检测己方；
	 * 一共检查：横3 竖3 斜2
	 * return 2: 出现己方2子
	 * return 1: 出现对方2子
	 * return 0: 无2子      */
	Dx = -1;
	Dy = -1;
	int CheckWho = -Turn; //检查谁有危险二子
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (Check1(i,j)==3 || Check2(i,j)==3 || Check3(i,j)==3){
				Dx = i; //己方2子，必填
				Dy = j;
				return 2;
			}
		}
	}
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (Check1(i,j)==2 || Check2(i,j)==2 || Check3(i,j)==2){
				Dx = i; //对方2子，必堵
				Dy = j;
				return 1;
			}
		}
	}
	return 0;
}

int CheckResult()
{	/* 不会出现双方同时连成三子的情况
	   return  0: 胜负未分
	   return -1: O获胜
	   return  1: X获胜 */
	int chess; //当前位置的棋子类型
	int ans;   //结果
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			chess = ChessBoard[i][j];
			if (chess){
				ans  = Check1(i,j);	
				if (ans) {
					return chess;
				}
				ans = Check2(i,j);
				if (ans) {
					return chess;
				}
				ans = Check3(i,j);
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
	cout << "+---+---+---+" << endl << endl;
}
