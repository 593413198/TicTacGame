#include "ChessBoard.h"
// 产生每一步当前的所有合理走法；
// 不用考虑走法的效益如何；

int ChessBoard[15][15];
int Turn;
int Round;

void GoStep(); 
