#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "puzzle.h"

using namespace std;

int main(void) {
  Puzzle *cPuzzle = new Puzzle; //pointer to current puzzle
  
  
  //for multiline, make sure to clear solutions
  while (!cin.eof()) {
    cout << "Solving...";
    clock_t begin =clock();
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
    
    clock_t end = clock();
  
  
    if (!Puzzle::solutions->empty()) {
      cout << *cPuzzle;
      //cout << "Passed! ";
    }
    else
      cout << "No solutions.\n";
    
    cout << "(" << double(end - begin) / CLOCKS_PER_SEC << ")" << endl;
    
    Puzzle::solutions->clear();
    cPuzzle = new Puzzle;
  }
  return 0;
} //main