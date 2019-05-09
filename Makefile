all:
	reset
	g++ ChessBoard.cpp PlayGame.cpp  -o test
	./test

