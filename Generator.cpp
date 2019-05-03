#include "Generator.h"
#include <stdio.h>
int ans = 0; //所有局面数量
char who[3] = {'O',' ','X'};
int times[3] = {0,0,0};

int Go(int depth){
	/* 表示进行到第depth回合
	 * depth%2=0: turn=-1 
	 * depth%2=1: turn=1  */
	if (depth==9){
		ans ++;
		times[1]++;
		//printf("ChessBoard Full!\n");
		return 1; //9回合到，棋盘落满，游戏结束
	}
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (ChessBoard[i][j]==0){ //找到空位置就落子
				if (depth%2 == 0) Turn = -1; //确定当前轮到谁落子
				else Turn = 1;
				ChessBoard[i][j] = Turn;
				//if (Turn==-1) printf("%d%d落子O\n",i+1,j+1);
				//if (Turn==1)  printf("%d%d落子X\n",i+1,j+1);
				int winner = CheckResult();
				if (!winner) //若未分出胜负，继续下一回合
					Go(depth+1);
				else{ //已分出胜负，不必继续搜索，回溯
					ShowBoard();
					times[winner+1] ++;
					ans ++;
					//printf("%c winner!\n",who[winner+1]);
					ChessBoard[i][j] = 0;
					return 0;
				}
				ChessBoard[i][j] = 0;
			}
		}
	}
}

int main(){
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			ChessBoard[i][j] = 0;
	Go(0);
	cout << ans << endl;
	printf("%d %d %d\n",times[0],times[2],times[1]);
}

