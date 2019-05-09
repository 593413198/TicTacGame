#include "PlayGame.h"
#include <stdio.h>
int ans = 0; //所有局面数量
int times[3] = {0,0,0}; //先手胜平负的局数统计
char Name[3] = {'O',' ','X'};
int NowTurn; //当前回合数
int WhoTurn; //记录当前局面轮到谁落子 
bool CanWin; //寻找是否有最终获胜的子节点
bool FirstTurn; //记录是否电脑先手
bool Over=0; //记录是否分出胜负


int MyStep() { //我方落子
	// 若FirstTurn =0,表示我方先手，
	int winner = CheckResult();
	if (winner){ //已经分出胜负
		cout << "很遗憾你输了!"<<endl;
		Over = 1;
		return 1;	
	}
	cout << "请输入您要下的位置坐标,如中心(2,2)"<<endl;
	int Mx,My;
	cin >> Mx >> My;
	Mx--;
	My--;
	cout << Mx << My << endl;
	while (ChessBoard[Mx][My]){ //该位置已经有棋子
		cout << "该位置已经有棋子，重新输入坐标:"<<endl;
		cin >> Mx >> My;
		Mx--;My--;
	}
	ChessBoard[Mx][My] = Turn;
	printf("您的落子位置是:(%d,%d)\n",Mx,My); 
	return 0;
}


int GoStep(){ //轮到电脑落子
	Evaluate();
	int winner = CheckResult();
	if (winner){
		cout << "恭喜你赢了!"<< endl;
		Over = 1;
		return 1; 
	}
	int ans = Check4();
	if (ans){ //己方2子，优先必填;对方2子，必堵
		ChessBoard[Dx][Dy] = Turn;
		printf("电脑的落子位置是:(%d,%d)\n",Dx,Dy); 
		return 0;
	}
	//对于电脑来说，只需要找到value最大的点位并落子即可
	int MaxX,MaxY,MaxValue=0;
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (!ChessBoard[i][j] && Value[i][j]>MaxValue){
				MaxX = i;
				MaxY = j;
				MaxValue = Value[i][j];
			}
		}
	}
	ChessBoard[MaxX][MaxY] = Turn;
	printf("电脑的落子位置是:(%d,%d)\n",MaxX,MaxY); 
	return 0;
}

int Go(int depth){
	/* 表示进行到第depth回合
	 * depth%2=0: turn=-1 
	 * depth%2=1: turn=1  */
	ShowBoard();
	ShowValue();
	int winner = CheckResult();
	Turn = (depth%2==0) ? -1:1;
	if (depth==9 || winner){
		return 1; //9回合到，棋盘落满，游戏结束
	}
	/* TODO 赋予初步智能：堵危险二子 */
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
	cout << "您是否选择先手? (输入0表示先手，输入1表示后手)"<<endl;
	cin >> FirstTurn; //0表示我方先手，1表示电脑先手
	Round = 0;
	if (FirstTurn==0) {//我方先手
		cout << "您是执'O'子的一方，并且是先手"<<endl;
		while (1){
			if (Over || Sum()==9)
				break;
			MyStep();
			ShowBoard();
			Round ++; Turn*=-1;
			if (Over || Sum()==9)
				break;
			GoStep(); 
			ShowBoard();
			Round ++; Turn*=-1;
		}
	}
	else { //电脑先手
		cout << "您是执'X'子的一方，并且是后手"<<endl;
		while (1){
			if (Over || Sum()==9)
				break;
			GoStep();
			ShowBoard();
			Round ++; Turn*=-1;
			if (Over || Sum()==9)
				break;
			MyStep();
			ShowBoard();
			Round ++; Turn*=-1;
		}
	}
	return 1;
}

