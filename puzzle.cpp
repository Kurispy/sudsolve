#include "puzzle.h"

using namespace std;

stack<Puzzle*> *Puzzle::alternatives = new stack<Puzzle*>;
vector<Puzzle*> *Puzzle::solutions = new vector<Puzzle*>;

Puzzle::Puzzle() {
  
}

Puzzle::Puzzle(int row, int col, int value, Puzzle *puzzle) {
  cells[row][col].cValues.insert(value);
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (i != row && j != col)
        cells[i][j].cValues = puzzle->cells[i][j].cValues;
}

void Puzzle::pushAlt(int row, int col, int value, Puzzle *puzzle) {
  Puzzle alternative(row, col, value, puzzle);
  alternatives->push(&alternative);
}

void Puzzle::updateRCS(int row, int col, int value) {
  //update row
  for (int i = 0; i < 9; i++)
    if (i != col)
      cells[row][i].eliminate(value);
  
  //update column
  for (int i = 0; i < 9; i++)
    if (i != row)
      cells[i][col].eliminate(value);
  
  //update square
  for (int i = 3 * (row / 3); i < 3 * (row / 3) + 3; i++)
    for (int j = 3 * (row / 3); j < 3 * (row / 3) + 3; j++)
      if (i != row && j != col)
        cells[i][j].eliminate(value);
}

void Puzzle::solve() {
  //eliminate known values from corresponding cell units
  //if any cell becomes solved, update again
  //continue until a cell has not been solved
  int x = 0;
  do {
    Cell::cellSolved = 0;
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
        if (cells[i][j].cValues.size() == 1)
          updateRCS(i, j, *(cells[i][j].cValues.begin())); //the first element of the first 3 rows is getting set to invalid
      x = x + 1;
  } while (Cell::cellSolved);
  
  //deductive methods go here
  
  
  
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
      }
    }
  
  if (solved)
    solutions->push_back(this);

}

void Puzzle::printSolutions() {
  for (unsigned int i = 0; i < solutions->size(); i++) {
    for (int j = 0; j < 9; j++)
      for (int k = 0; k < 9; k++)
        cout << *(solutions->at(i)->cells[j][k].cValues.begin());
    
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
      else if (isprint(test)) {
        if (test >= (int) '1' && test <= (int) '9') {
          puzzle.cells[i][j].cValues.insert(test - '0'); //valid value; convert to integer
          puzzle.cells[i][j].isSolved = 1;
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
  

  // <editor-fold defaultstate="collapsed" desc="SINGLE LINE FILES">
  test = is.get();
  test = is.get(); //weird
  
  if (!is.eof()) {
    cout << "ERROR: expected <eof> saw ";
    if (isprint(test)) {
      cout << (char) test << "\n";
      exit(0);
    } else {
      cout << "\\x" << setw(2) << setfill('0') << hex << test << "\n";
      exit(0);
    }
  }// </editor-fold>

  return is;
}

ostream& operator<< (ostream &os, const Puzzle &puzzle) {
  puzzle.printSolutions();
  
  return os;
}