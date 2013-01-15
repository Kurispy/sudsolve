#include "puzzle.h"

using namespace std;

stack<Puzzle*> *Puzzle::alternatives = new stack<Puzzle*>;
vector<Puzzle> *Puzzle::solutions = new vector<Puzzle>;

Puzzle::Puzzle()
:solved(0) {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      cells[i][j].row = i;
      cells[i][j].col = j;
      cells[i][j].square = (i / 3) + (j / 3); 
    }
}

Puzzle::Puzzle(int row, int col, int value, Puzzle *puzzle)
:solved(0) {
  //decide the value of a single undetermined cell
  cells[row][col].cValues.insert(value);
  cells[row][col].isSolved = 1;
  cells[row][col].invalidCell = 0;
  cells[row][col].row = row;
  cells[row][col].col = col;
  cells[row][col].square = (row / 3) + (col / 3);
  solvedCells.push(cells[row][col]);

  
  //leave the rest the same
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (i != row || j != col)
        cells[i][j] = puzzle->cells[i][j];
}

void Puzzle::checkAlt() {
  //if the puzzle has not been solved, we need to guess and check every possible alternative
  solved = 1;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      if (cells[i][j].invalidCell) //dead end
        return;
      else if (!cells[i][j].isSolved) {
        solved = 0;
        for (int k = 1; k < 10; k++)
          if(cells[i][j].cValues.find(k) != cells[i][j].cValues.end())
            pushAlt(i, j, k);
        return;
      }
    }
}

void Puzzle::pushAlt(int row, int col, int value) {
  Puzzle *alternative = new Puzzle(row, col, value, this);
  alternatives->push(alternative);
}

void Puzzle::updateRCS(Cell &cell) {
  //update row
  for (int i = 0; i < 9; i++)
    if (i != cell.col)
      cells[cell.row][i].eliminate(*(cell.cValues.begin()), *this);
  
  //update column
  for (int i = 0; i < 9; i++)
    if (i != cell.row)
      cells[i][cell.col].eliminate(*(cell.cValues.begin()), *this);
  
  //update square
  for (int i = 3 * (cell.row / 3); i < 3 * (cell.row / 3) + 3; i++)
    for (int j = 3 * (cell.col / 3); j < 3 * (cell.col / 3) + 3; j++)
      if (i != cell.row || j != cell.col)
        cells[i][j].eliminate(*(cell.cValues.begin()), *this);
}

void Puzzle::svEliminate() {
  //eliminate known values from corresponding cell units
  //if any cell becomes solved, update again
  //continue until a cell has not been solved
  while (!solvedCells.empty()) {
    updateRCS(solvedCells.front());
    solvedCells.pop();
  }
}

void Puzzle::sgExclusion() {
  set<int>::iterator itr;
  
  //Find a cell that has not been solved
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      if (!cells[i][j].isSolved) {
        //iterate through each candidate value, applying sgExclusion to each
        for (itr = cells[i][j].cValues.begin(); itr != cells[i][j].cValues.end(); itr++) {
          sgExclusionR(i, *itr);
          sgExclusionC(j, *itr);
          svEliminate(); //we might have solved some cells, so we need to eliminate those solved values
        }
      }
    }
}

void Puzzle::sgExclusionR(int row, int value) {
  //if all cells that hold candidacy for a particular number in a particular row or column lie within the same square, 
  //that number can be eliminated from the candidate list of all other cells in the square
  
  //the value argument must be a candidate in at least 2 cells
  
  //check row
  int square = -1;
  for (int i = 0; i < 9; i++) {
    if (!cells[row][i].isSolved && cells[row][i].cValues.find(value) != cells[row][i].cValues.end()) {
      if (cells[row][i].square == square)
        square = cells[row][i].square;
      else if (square != -1)
        return; //the cells with the values are in different squares and this rule cannot be used
    }
  }
  
  //all conditions cleared; eliminate this value from all cells in the square that are not in this row
  for (int i = (square / 3) * 3; i < (square / 3) * 3 + 3; i++)
    for (int j = (square % 3) * 3; j < (square % 3) * 3 + 3; j++)
      if (i != row)
        cells[i][j].eliminate(value, *this);
}

void Puzzle::sgExclusionC(int col, int value) {
  //the value argument must be a candidate in at least 2 cells
  
  //check column
  int square = -1;
  for (int i = 0; i < 9; i++) {
    if (!cells[i][col].isSolved && cells[i][col].cValues.find(value) != cells[i][col].cValues.end()) {
      if (cells[i][col].square == square)
        square = cells[i][col].square;
      else if (square != -1)
        return; //the cells with the values are in different squares and this rule cannot be used
    }
  }
  
  //all conditions cleared; eliminate this value from all cells in the square that are not in this row
  for (int i = (square / 3) * 3; i < (square / 3) * 3 + 3; i++)
    for (int j = (square % 3) * 3; j < (square % 3) * 3 + 3; j++)
      if (i != col)
        cells[i][j].eliminate(value, *this);
}

void Puzzle::solve() {
  //Single Value Elimination
  svEliminate();
  
  //DEDUCTIVE STRATEGIES
  
  //Sub-Group Exclusion
  //sgExclusion();
  
  
  
  //printPossible();
  
  //Check if the puzzle is solved, and if we need to create alternatives
  checkAlt();
  
  if (solved) {
    solutions->push_back(*this);
  }

}

void Puzzle::printPossible() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << "[";
      for (int k = 1; k < 10; k++) {
        if (cells[i][j].cValues.find(k) != cells[i][j].cValues.end())
          cout << *(cells[i][j].cValues.find(k));
        else
          cout << " ";
      }
      cout << "]" << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void Puzzle::printSolutions() {
  for (unsigned int i = 0; i < solutions->size(); i++) {
    for (int j = 0; j < 9; j++)
      for (int k = 0; k < 9; k++)
        cout << *(solutions->at(i).cells[j][k].cValues.begin());
    
    cout << "\n";
  }
}


istream& operator>> (istream &is, Puzzle &puzzle) {
  //We need to parse stdin until we read an unexpected or character, or an EOF
  int test;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      test = is.get();
      if (is.eof()) {
        cout << "ERROR: expected <value> saw <eof>\n";
        exit(0);
      }
      else if (test == (int) '\n') {
        cout << "ERROR: expected <value> saw " << "\\n" << "\n";
        exit(0);
      }
      else if (isprint(test)) {
        if (test >= (int) '1' && test <= (int) '9') {
          puzzle.cells[i][j].cValues.insert(test - '0'); //valid value; convert to integer
          puzzle.cells[i][j].isSolved = 1;
          puzzle.solvedCells.push(puzzle.cells[i][j]);
        }
        else if (test == (int) '.') {
          for (int k = 1; k < 10; k++)
            puzzle.cells[i][j].cValues.insert(k);
        }
        else { //printable unexpected character
          cout << "ERROR: expected <value> saw " << (char) test << "\n";
          exit(0);
        }
      }
      else { //unprintable unexpected character
        cout << "ERROR: expected <value> saw \\x" << setw(2) << setfill('0') << hex << test << "\n";
        exit(0);
      }
    }
  }
  //now we expect \n and then EOF
  test = is.get();
  if (is.eof()) {
      cout << "ERROR: expected \\n saw <eof>\n";
      exit(0);
  }
  else if (test != '\n'){
    cout << "ERROR: expected \\n saw ";
    if (isprint(test)) {
      cout << (char) test << "\n";
      exit(0);
    }
    else {
      cout << "\\x" << setw(2) << setfill('0') << hex << test << "\n";
      exit(0);
    }
  }
  

//  // <editor-fold defaultstate="collapsed" desc="SINGLE LINE FILES">
//  test = is.get();
//  test = is.get(); //weird
//  
//  if (!is.eof()) {
//    cout << "ERROR: expected <eof> saw ";
//    if (isprint(test)) {
//      cout << (char) test << "\n";
//      exit(0);
//    }
//    else if (test == (int) '\n') {
//      cout << "\\n" << "\n";
//      exit(0);
//    }
//    else {
//      cout << "\\x" << setw(2) << setfill('0') << hex << test << "\n";
//      exit(0);
//    }
//  }// </editor-fold>

  return is;
}

ostream& operator<< (ostream &os, const Puzzle &puzzle) {
  puzzle.printSolutions();
  
  return os;
}