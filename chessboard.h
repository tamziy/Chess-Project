#include <iostream>
#include <iterator>
using namespace std;

// define separate containers for Color, Piece (enums recommended)
enum Color { White, Black, UndefinedColor };
enum Piece { King, Queen, Rook, Knight, Bishop, Pawn, UndefinedPiece };

// Squares for the Chessboard Game
class Square {

private:
  Color color;
  Piece piece;
  bool occupied;

public:
  // default, square unoccupied
  Square(); 
    
  // an occupied square
  Square(Color c, Piece p);

  // information about the square
  int get(bool &o, Color &c, Piece &p);

  // printing out information about the square
  void print();
};

class ChessboardIterator;

class Chessboard {
  // make the container iterator friendly
  typedef ChessboardIterator iterator;

private:
  Square chessboard[8][8];

public:
  friend class ChessboardIterator;

  Chessboard() {} // Square does all the initialization

  // return an x,y square from chessboard
  Square square(int x, int y) {
    // fill out
  }

  ChessboardIterator begin();
  ChessboardIterator end();

  // place a piece on a x,y square in the chessboard
  int place(int x, int y, Color c, Piece p) {
    // fill out
  }
  int get(int x, int y, Color &c, Piece &p) {
    // fill out
  }

  int move(int fromX, int fromY, int toX, int toY) {
    // fill out
  }

  void print();
};

class ChessboardIterator {
private:
  int position; // a number in [0..63]
  Chessboard chessboard;

public:
  ChessboardIterator(Chessboard &board,
                     int pos) { // start out with an empty board
    // fill out
  }

  void xy(int &x, int &y) { // break position down into x and y
    // fill out
  }

  // return the square
  Square operator*() {
    // fill out
  }

  // pre-increment
  ChessboardIterator &operator++() {
    // fill out
  }

  // needed to support foreach
  int operator!=(ChessboardIterator &a) {
    // fill out
  }
};
