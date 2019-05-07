#include "ChessBoard.h"
#include "PlayGame.h"

int f(int n){
	if (n!=10){
		f(n+1);
		cout << n << endl;
	}
	if (n==10)
		return 1;

}

int main(){
	//ChessBoard[0][0] = -1;
	//ChessBoard[1][1] = -1;
	//ChessBoard[2][2] = -1;
	//GoStep(1);	
	f(1);
	return 1;
}
