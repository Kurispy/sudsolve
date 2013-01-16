# tech; Chen, Christopher
sudsolve : cell.o main.o puzzle.o 
	g++ -Wall -g -o sudsolve  cell.o main.o puzzle.o 

cell.o : cell.cpp cell.h 
	g++ -Wall -g -c  cell.cpp

main.o : main.cpp puzzle.h 
	g++ -Wall -g -c  main.cpp

puzzle.o : puzzle.cpp puzzle.h 
	g++ -Wall -g -c  puzzle.cpp

clean:
	rm -f sudsolve cell.o main.o puzzle.o 