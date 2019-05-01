#include "Generator.h"
int ans = 0; //所有局面数量

int Go(int depth){
	/* 表示进行到第depth回合
	 * depth%2=0: turn=-1 
	 * depth%2=1: turn=1  */
	if (depth%2 == 0) Turn = -1; //确定当前轮到谁落子
	else Turn = 1;
	if (depth==9){
		ans ++;
		cout << "棋盘下满"<<endl;
		return 1; //9回合到，棋盘落满，游戏结束
	}
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (ChessBoard[i][j]==0){ //找到空位置就落子
				ChessBoard[i][j] = Turn;
			}
			int winner = CheckResult();
			if (!winner) //若未分出胜负，继续下一回合
				Go(depth+1);
			else{//已分出胜负，不必继续搜索，回溯
				cout << winner << "获胜" << endl;
				ChessBoard[i][j] = 0;
			}
		}
	}	
}

int main(){
	Go(0);
	cout << ans << endl;
}

