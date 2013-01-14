#include "cell.h"

bool Cell::cellSolved = 0;

void Cell::eliminate(int value) {
  if (cValues.erase(value) && cValues.size() == 1) {
    cellSolved = 1;
    isSolved = 1;
  }
  else if (cValues.empty()) 
    invalidCell = 1;
}

