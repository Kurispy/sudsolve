#include <cstdio>
#include <cstdlib>
#include "puzzle.h"

using namespace std;

int main(void) {
  Puzzle *cPuzzle; //pointer to current puzzle
  cin >> *cPuzzle;
  
  //for multiline, make sure to clear solutions
  
  Puzzle::alternatives->push(cPuzzle);
  while (!Puzzle::alternatives->empty()) {
    cPuzzle = Puzzle::alternatives->top();
    Puzzle::alternatives->pop();
    cPuzzle->solve();
  }
  
  if (!Puzzle::solutions->empty())
    cout << *cPuzzle;
  else
    cout << "No solutions.\n";
  
  return 0;
} //main