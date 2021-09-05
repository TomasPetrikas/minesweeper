Demo : demo.cpp Minesweeper.o demo.o
	g++ -std=c++11 Minesweeper.o demo.o -o Demo.exe
Test : test.cpp Minesweeper.o test.o
	g++ -std=c++11 Minesweeper.o test.o -o Test.exe
Minesweeper.o : Minesweeper.cpp Minesweeper.h
	g++ -std=c++11 Minesweeper.cpp -c
demo.o : demo.cpp Minesweeper.h
	g++ -std=c++11 demo.cpp -c
test.o : test.cpp Minesweeper.h
	g++ -std=c++11 test.cpp -c