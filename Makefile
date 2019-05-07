all:
	reset
	g++ ChessBoard.cpp PlayGame.cpp  -o test
	./test < example.c  > result.c 

