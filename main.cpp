#include <cstdio>
#include <cstdlib>
#include "puzzle.h"

using namespace std;

int main(void) {
  Puzzle *cPuzzle = new Puzzle; //pointer to current puzzle
  
  
  //for multiline, make sure to clear solutions
  while (!cin.eof()) {
    cin >> *cPuzzle;
    Puzzle::alternatives->push(cPuzzle);
    while (!Puzzle::alternatives->empty()) {
      //cout << Puzzle::alternatives->size() << endl;
      cPuzzle = Puzzle::alternatives->top();
      Puzzle::alternatives->pop();
      cPuzzle->solve();
      delete cPuzzle;
      cPuzzle = NULL;
    }
    
  }
  
  if (!Puzzle::solutions->empty()) {
    cout << *cPuzzle;
    cout << "Passed!";
  }
  else
    cout << "No solutions.\n";
  
  return 0;
} //main