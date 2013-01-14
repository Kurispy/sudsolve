#include "puzzle.h"

using namespace std;

stack<Puzzle*> *Puzzle::alternatives = new stack<Puzzle*>;
vector< vector<int> > *Puzzle::solutions = new vector< vector<int> >;

Puzzle::Puzzle() {
  
}

Puzzle::Puzzle(Puzzle *puzzle) {
  
}

void Puzzle::updateRCS(int row, int col, int value) {
  //update row
  
  
  //update column
  
  
  //update square
  
  
  
}

void Puzzle::solve() {
  //eliminate known values from corresponding cell units
  //if any cell becomes solved, update again
  //continue until a cell has not been solved
  while (Cell::cellSolved) {
    Cell::cellSolved = 0;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (cells[i][j].cValues.size() == 1)
          updateRCS(i, j, *(cells[i][j].cValues.begin()));
      }
    }
  }
  
  //deductive methods go here
  
  
  
  
  //if the puzzle has not been solved, we need to guess and check every possible alternative
  //set an unsolved cell to solved, then call solve on that puzzle
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (!cells[i][j].isSolved){
        Puzzle alternative(this);
        for (int k = 1; k < 10; k++) {
          if(cells[i][j].cValues.find(k) != cells[i][j].cValues.end()) {
            cells[i][j].cValues.clear();
            cells[i][j].cValues.insert(k);
          }
        }
        cells[i][j].isSolved = 1;
        Cell::cellSolved = 1;
      }
    }
  }

}

void Puzzle::printSolutions() {
  
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
        if (test >= (int) '1' && test <= (int) '9')
          puzzle.cells[i][j].cValues.insert(test - '0'); //valid value; convert to integer
        else if (test == (int) '.')
          puzzle.cells[i][j].cValues.insert(0);
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
      cout << "ERROR: expected <value> saw <eof>\n";
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
  if (!is.eof()) {
    cout << "ERROR: expected <eof> saw ";
    if (isprint(test)) {
      cout << (char) test << "\n";
      exit(0);
    } else {
      cout << "\\x" << hex << test << "\n";
      exit(0);
    }
  }// </editor-fold>

  return is;
}

ostream& operator<< (ostream &os, const Puzzle &puzzle) {
  
  
  return os;
}