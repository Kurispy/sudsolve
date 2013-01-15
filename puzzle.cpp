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

void Puzzle::pushAlt(int row, int col, int value, Puzzle *puzzle) {
  Puzzle *alternative = new Puzzle(row, col, value, puzzle);
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

void Puzzle::solve() {
  //eliminate known values from corresponding cell units
  //if any cell becomes solved, update again
  //continue until a cell has not been solved
  
  while (!solvedCells.empty()) {
    updateRCS(solvedCells.front());
    solvedCells.pop();
  }
  
  //deductive strategies
  onlySquare();
  
  //printPossible();
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
            pushAlt(i, j, k, this);
        return;
      }
    }
  
  if (solved) {
    solutions->push_back(*this);
  }

}

void Puzzle::onlySquare() {
  //if there is only one place to allocate the last value in a square, put the value there
  
  //search for a given value within a square
  for (int i = 1; i < 10; i++) {
    for (int j = 0; j < 9; j++) {
      for (int k = 0; k < 9; k++) {
        for (int l = 0; l < 9; l++) {
          if (l == cells[j][k].square && cells[j][k].cValues.find(i) != cells[j][k].cValues.end()) {
            
          } 
        }
      }
    }
  }
  
  //if only one cell has that value, set it to that value
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