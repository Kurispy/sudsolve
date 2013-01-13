#ifndef PUZZLE_H
#define	PUZZLE_H

#include <iostream>

class Puzzle {
  int puzzle[81];
public:
  void solve(void);
  friend istream& operator>> (istream &is, Puzzle &puzzle);
  friend ostream& operator<< (ostream &os, const Puzzle &puzzle);
  
  
  
}; //class Puzzle


#endif	/* PUZZLE_H */

