all:
	reset
	g++ ChessBoard.cpp test.cpp -o test
	./test

