#include <iostream>
using namespace std;

#define O -1   //代表落子"O",先手
#define X 1    //代表落子"X",后手
#define NONE 0 //代表此处无子
extern int Round; //回合数
extern int Turn;  //当前轮到谁落子 
extern int ChessBoard[3][3]; //代表3x3的棋盘

void Run();         //走完一个回合，回合数加1
int  CheckResult();  //检测是否已连成5子
bool Check1(int i, int j); //检测在(i,j)处的棋子水平方向是否成3子
bool Check2(int i, int j); //竖直方向
bool Check3(int i, int j); //对角线方向

