#include "cell.h"

bool Cell::invalidCell = 0;
bool Cell::cellSolved = 0;

void Cell::update(int value) {
  
  
  
  if (cValues.size() == 1) {
    cellSolved = 1;
    isSolved = 1;
  }
  else if (cValues.empty()) 
    invalidCell = 1;
}

