#include "ChessBoard.h"

int Go(int depth); //递归产生所有的局面
bool Input(); 
/* 给一个手动输入棋盘的接口，测试用;
 * 轮到谁下就为谁判断能否赢 */
int Sum(); //统计已经下的棋子数，即回合数
