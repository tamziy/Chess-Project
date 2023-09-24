// chessboard.cpp

#include "chessboard.h"

/**
 
  Square

**/

//Default Square
Square::Square() {
  color = UndefinedColor;
  piece = UndefinedPiece;
  occupied = false;
}

//Occupied Square
Square::Square(Color c, Piece p) {
  color = c;
  piece = p;
  occupied = true;
}

//Information about the square
int Square::get(bool &o, Color &c, Piece &p) {
  o = occupied;
  c = color;
  p = piece;
  return 0;
}

//Printing square information
void Square::print() {
  if (occupied) {
    cout << "Square is occupied with a " << color << " " << piece << endl;
  } else {
    cout << "Square is unoccupied" << endl;
  }
}








// define containers for color mappings (2 colors) and piece mappings (6 pieces)

ChessboardIterator Chessboard::begin() {
  // fill out
}

ChessboardIterator Chessboard::end() {
  // fill out
}

// print the chessboard with white at the bottom (traditional view)
void Chessboard::print() {
  // fill out
}