#include "puzzle.h"

using namespace std;

void Puzzle::solve() {
  
}








istream& operator>> (istream &is, Puzzle &puzzle) {
  //We need to parse stdin until we read an unexpected or character, or an EOF
  
  //single line version
  for (int i = 0; i < 81; i++) {
    puzzle[i] = is.get();
    if (is.eof()) {
      cout << "ERROR: expected <value> saw <eof>\n";
      exit(0);
    }
    else if (isprint(puzzle[i])) {
      if (puzzle[i] >= (int) '1' && puzzle[i] <= (int) '9')
        puzzle[i] = puzzle[i] - '0'; //valid value; convert to integer
      else if (puzzle[i] == (int) '.')
        puzzle [i] = 0;
      else { //printable unexpected character
        cout << "ERROR: expected <value> saw " << (char) puzzle[i] << "\n";
        exit(0);
      }
    }
    else { //unprintable unexpected character
      cout << "ERROR: expected <value> saw \\x" << hex << puzzle[i] << "\n";
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
      cout << "\\x" << hex << test << "\n";
      exit(0);
    }
  }
  test = is.get();
  if (!is.eof()) {
    cout << "ERROR: expected <eof> saw ";
    if (isprint(test)) {
      cout << (char) test << "\n";
      exit(0);
    }
    else {
      cout << "\\x" << hex << test << "\n";
      exit(0);
    }
  }
  return is;
}

ostream& operator<< (ostream &os, const Puzzle &puzzle) {
  
}