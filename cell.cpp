#include "cell.h"

bool Cell::cellSolved = 0;

void Cell::eliminate(int value) {
  cValues.erase(value);
  
  if (cValues.size() == 1) {
    cellSolved = 1;
    isSolved = 1;
  }
  else if (cValues.empty()) 
    invalidCell = 1;
}

