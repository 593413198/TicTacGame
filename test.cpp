#include "ChessBoard.h"

int main(){
	ChessBoard[0][0] = -1;
	ChessBoard[1][1] = -1;
	ChessBoard[2][2] = -1;
	int i = CheckResult();
	cout << i << endl;
	
	return 1;
}
