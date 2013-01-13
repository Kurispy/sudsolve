#ifndef PUZZLE_H
#define	PUZZLE_H

#include <iostream>
#include <cstdlib>

using namespace std;

class Puzzle {
  int gValues[81]; //given values
public:
  void solve(void);
  friend istream& operator>> (istream &is, Puzzle &puzzle);
  friend ostream& operator<< (ostream &os, const Puzzle &puzzle);
  
  
  
}; //class Puzzle


#endif	/* PUZZLE_H */

