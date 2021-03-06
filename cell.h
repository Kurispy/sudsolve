#ifndef CELL_H
#define	CELL_H

#include <set>

using namespace std;

class Puzzle;

class Cell {
public:
  Cell();
  int row;
  int col;
  int square;
  set<int> cValues; //could be changed to unordered_set
  bool isSolved;
  void eliminate(int value, Puzzle &puzzle, bool *valid); //returns 0 if a cell was invalidated, 1 otherwise
  void onlyCell(int value, Puzzle &puzzle);
  Cell& operator=(const Cell &rhs);
};

#endif	/* CELL_H */

