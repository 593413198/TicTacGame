all:
	reset
	g++ ChessBoard.cpp Generator.cpp  -o test
	./test

