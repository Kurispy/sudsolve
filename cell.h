#ifndef CELL_H
#define	CELL_H

#include <set>

using namespace std;

class Cell {
public:
  bool isSolved;
  static bool invalidCell; //flag set when a cell is reduced to 0 candidates
  static bool cellSolved; //flag set when a cell is solved
  set<int> cValues;
  void update(int value);

};

#endif	/* CELL_H */

