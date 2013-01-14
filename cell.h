#ifndef CELL_H
#define	CELL_H

#include <set>

using namespace std;

class Cell {
public:
  bool isSolved;
  bool invalidCell;
  static bool cellSolved; //flag set when a cell is solved
  set<int> cValues;
  void eliminate(int value);
};

#endif	/* CELL_H */

