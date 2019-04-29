#include <stdio.h>
#include <iostream>

#define O -1   //代表落子"O",先手
#define X 1    //代表落子"X",后手
#define NONE 0 //代表此处无子
int Round = 1; //回合数
int Turn  = 0; //当前轮到谁落子 
int ChessBoard[3][3]; //代表3x3的棋盘

void Run();    //走完一个回合，回合数加1
int CheckResult();  //检测是否已连成5子
int CheckLeftDown(int chess, int i, int j); //检测chess棋子在(i,j)处的左下方是否连成5子
int CheckDown(int chess, int i, int j);     //正下方
int CheckRightDown(int chess, int i, int j);//右下方
int CheckRight(int chess, int i, int j);    //正右方

void Run()
{	
	Round ++; //回合数加1
	Turn  = 1 - Turn; //更换落子方
}
