#ifndef PUZZLE_H
#define	PUZZLE_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>
#include "cell.h"

using namespace std;

class Puzzle {
  int gValues[81]; //given valuess
  Cell cells[9][9];
  vector< vector<int> > solutions;
  bool cellSolved;
  void givenToCand();
  void updateRCS(int row, int col, int value);
public:
  void solve();
  friend istream& operator>> (istream &is, Puzzle &puzzle);
  friend ostream& operator<< (ostream &os, const Puzzle &puzzle);
  
  
  
}; //class Puzzle


#endif	/* PUZZLE_H */

