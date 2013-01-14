#ifndef PUZZLE_H
#define	PUZZLE_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stack>
#include <vector>
#include <list>
#include "cell.h"

using namespace std;

class Puzzle {
  Cell cells[9][9];
  void updateRCS(int row, int col, int value);
public:
  static stack<Puzzle*> *alternatives;
  static vector< vector<int> > *solutions;
  Puzzle();
  Puzzle(Puzzle *puzzle);
  static void printSolutions();
  void solve();
  friend istream& operator>> (istream &is, Puzzle &puzzle);
  friend ostream& operator<< (ostream &os, const Puzzle &puzzle);
  
  
  
}; //class Puzzle


#endif	/* PUZZLE_H */

