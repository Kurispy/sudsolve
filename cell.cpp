#include "cell.h"
#include "puzzle.h"

Cell::Cell()
:isSolved(0) {
  
}

void Cell::eliminate(int value, Puzzle &puzzle, bool *valid) {
  if (cValues.erase(value) && cValues.size() == 1 && !isSolved) {
      puzzle.solvedCells.push(*this);
      isSolved = 1;
  }
  else if (cValues.empty()) {
    *valid = 0;
    return;
  }
}

Cell& Cell::operator=(const Cell &rhs) {
  row = rhs.row;
  col = rhs.col;
  square = rhs.square;
  cValues = rhs.cValues;
  isSolved = rhs.isSolved;
  return *this;
}