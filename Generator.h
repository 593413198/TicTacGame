#include "ChessBoard.h"
extern int Mark[3][3];  //用于回溯法记录是否已走过
extern int tmp_i,tmp_j; //记录每一步走法的落子位置
extern int Depth; //全剧变量，搜索树深度

void InitMark(); //重置回溯的标记

int GoStep(int Turn); //产生当前棋型的所有有效走法; 同时检测是否走满

int Go(int depth); //递归产生所有的局面

