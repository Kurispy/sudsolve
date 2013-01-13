#include "puzzle.h"

using namespace std;

void Puzzle::givenToCand() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (gValues[i])
        cValues[i][j].insert(gValues[i]);
      else
        for (int k = 1; k < 10; k++)
          cValues[i][j].insert(k);
    }
  }
}

void Puzzle::updateRCS(int row, int col, int value) {
  
}

void Puzzle::solve() {
  //assumes puzzle looks solvable
  
  //initialize candidate list with gValues
  givenToCand();
  
  //could start loop here
  //eliminate known values from corresponding cell units
  
  //if any cell becomes solved, update again
  //continue until a cell has not been solved
  
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (cValues[i][j].size() == 1)
        updateRCS(i, j, *cValues[i][j].begin());
    }
  }
  

}






istream& operator>> (istream &is, Puzzle &puzzle) {
  //We need to parse stdin until we read an unexpected or character, or an EOF
  
  for (int i = 0; i < 81; i++) {
    puzzle.gValues[i] = is.get();
    if (is.eof()) {
      cout << "ERROR: expected <value> saw <eof>\n";
      exit(0);
    }
    else if (isprint(puzzle.gValues[i])) {
      if (puzzle.gValues[i] >= (int) '1' && puzzle.gValues[i] <= (int) '9')
        puzzle.gValues[i] = puzzle.gValues[i] - '0'; //valid value; convert to integer
      else if (puzzle.gValues[i] == (int) '.')
        puzzle.gValues[i] = 0;
      else { //printable unexpected character
        cout << "ERROR: expected <value> saw " << (char) puzzle.gValues[i] << "\n";
        exit(0);
      }
    }
    else { //unprintable unexpected character
      cout << "ERROR: expected <value> saw \\x" << setw(2) << setfill('0') << hex << puzzle.gValues[i] << "\n";
      exit(0);
    }
  }
  //now we expect \n and then EOF
  int test = is.get();
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