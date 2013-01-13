#include <cstdio>
#include <cstdlib>
#include "puzzle.h"

using namespace std;

int main(void) {
  Puzzle *puzzle = new Puzzle;
  cin >> *puzzle;
  
  //proper input; solve puzzle
  //may have to implement a stack of alternatives here
  puzzle->solve();
  cout << *puzzle;
  
  return 0;
} //main