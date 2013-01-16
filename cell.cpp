#include "cell.h"
#include "puzzle.h"

Cell::Cell()
:isSolved(0) {
  
}

void Cell::eliminate(int value, Puzzle &puzzle, bool *valid) {
  if (cValues.erase(value) && cValues.size() == 1 && !isSolved) {
    isSolved = 1;
    puzzle.solvedCells.push(*this);
  }
  else if (cValues.empty()) {
    *valid = 0;
    return;
  }
}

void Cell::onlyCell(int value, Puzzle &puzzle) {
  //If there exists in a given row or column a cell such that it contains the only occurance of a given value 
  //and that cell is not solved, the cell must contain that value
  
  cValues.clear();
  cValues.insert(value);
  isSolved = 1;
  puzzle.solvedCells.push(*this);
}

Cell& Cell::operator=(const Cell &rhs) {
  row = rhs.row;
  col = rhs.col;
  square = rhs.square;
  cValues = rhs.cValues;
  isSolved = rhs.isSolved;
  return *this;
}