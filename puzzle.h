#ifndef PUZZLE_H
#define	PUZZLE_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stack>
#include <vector>
#include <queue>
#include "cell.h"

using namespace std;

class Puzzle {
  bool solved;
  Cell cells[9][9];
  void updateRCS(Cell &cell);
public:
  queue<Cell> solvedCells;
  static stack<Puzzle*> *alternatives;
  static vector<Puzzle> *solutions;
  Puzzle();
  Puzzle(int row, int col, int value, Puzzle *puzzle);
  void pushAlt(int row, int col, int value, Puzzle *puzzle);
  static void printSolutions();
  void printPossible();
  void solve();
  void onlySquare();
  friend istream& operator>> (istream &is, Puzzle &puzzle);
  friend ostream& operator<< (ostream &os, const Puzzle &puzzle);
  
  
  
}; //class Puzzle


#endif	/* PUZZLE_H */

