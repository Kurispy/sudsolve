#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "puzzle.h"

using namespace std;

//Sudoku is hard,
//however with this program,
//it's very easy.

int main(void) {
  Puzzle *cPuzzle = new Puzzle; //pointer to current puzzle
  
  cin >> *cPuzzle;
  Puzzle::alternatives->push(cPuzzle);
  while (!Puzzle::alternatives->empty()) {
    cPuzzle = Puzzle::alternatives->top();
    Puzzle::alternatives->pop();
    cPuzzle->solve();
    delete cPuzzle;
    cPuzzle = NULL;
  }
  
    if (!Puzzle::solutions->empty()) {
      cout << *cPuzzle;
    }
    else
      cout << "No solutions.\n";
    
  return 0;
} //main