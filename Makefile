all:
	reset
	g++ ChessBoard.cpp Generator.cpp test.cpp -o test
	./test

