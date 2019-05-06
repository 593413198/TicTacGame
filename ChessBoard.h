#include <iostream>
#include <stdio.h>
using namespace std;

#define O -1   //代表落子"O",先手
#define X 1    //代表落子"X",后手
#define NONE 0 //代表此处无子
extern int Round; //回合数
extern int Turn;  //当前轮到谁落子 
extern int ChessBoard[3][3];  //代表3x3的棋盘
extern int Dx,Dy; //堵对手出现连二子的位置

int  CheckResult();  //检测是否已连成3子
bool Check1(int i, int j); //水平方向
bool Check2(int i, int j); //竖直方向
bool Check3(int i, int j); //对角线方向

int  Check4(); //检测对手是否出现危险二子，必封堵
void ShowBoard(); //打印图形界面
