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
  set<int> cValues;
  bool isSolved;
  bool invalidCell;
  void eliminate(int value, Puzzle &puzzle);
  Cell& operator=(const Cell &rhs);
};

#endif	/* CELL_H */

