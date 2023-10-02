/**
 * Author: Tam Le
 * UIN: 674428071
 * File: chessboard.h
 * Project: Chessboard Project for CS 341
 * Description:
 * A C++ project that displays an 8x8 chessboard
 * with an iterator over the chessboard. The view
 * of the board is traditional view.
*/

#include <iostream>
#include <iterator>
using namespace std;

// Enumerations for all the possible colors and pieces of Chess
enum Color { White, Black, UndefinedColor };
enum Piece { King, Queen, Rook, Knight, Bishop, Pawn, UndefinedPiece };

// Class that represents an individual square on the Chessboard
class Square {

private:
  Color color;
  Piece piece;
  bool occupied;

public:
  // Default constructor, square unoccupied
  Square() {
    color = UndefinedColor;
    piece = UndefinedPiece;
    occupied = false;
  }
    
  // Constructor for an occupied square
  Square(Color c, Piece p) {
    color = c;
    piece = p;
    occupied = true;
  }  

  // A getter method for information on the square
  int get(bool &o, Color &c, Piece &p) {
    o = occupied;
    c = color;
    p = piece;
    return 0;
  }

  // Printing out information about the square
  void print() {
    if (occupied) {
      string colorStr;

      if (color == White) {
         colorStr = "b";
      } else if (color == Black) {
         colorStr = "w";
      }

      string pieceStr;

      switch(piece) {
        case 0:
          pieceStr = "K";
          break;
        
        case 1:
          pieceStr = "Q";
          break;

        case 2:
          pieceStr = "R";
          break;
        
        case 4:
          pieceStr = "B";
          break;

        case 3:
          pieceStr = "N";
          break;
        
        case 5:
          pieceStr = "P";
          break;

        default:
          pieceStr = "?";
          break;
      }

      cout << colorStr << pieceStr << " ";

    } else {
      cout << " . ";
    }
  }
};

// Forward Declaration for the iterator
class ChessboardIterator;

//Class for the main Chessboard Game
class Chessboard {
  // Make the container iterator friendly
  typedef ChessboardIterator iterator;

private:
//8x8 chessboard of Squares
  Square chessboard[8][8];

public:
  friend class ChessboardIterator;

  Chessboard() {} // Square does all the initialization

  // Return an x,y square from chessboard
  Square square(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
      return chessboard[x][y];
    } 
  }

  ChessboardIterator begin();
  ChessboardIterator end();

  //Placing a piece on the board
  int place(int x, int y, Color c, Piece p) {
    if (x < 0 || x >= 8) {
      return -1;
    }
    
    if (y < 0 || y >= 8) {
      return -2;
    }

    bool occupied;
    Color existingColor;
    Piece ExistingPiece;
    chessboard[x][y].get(occupied, existingColor, ExistingPiece);

    if (occupied) { 
      return -3;
    }

    if (c != White && c != Black) {
      return -4;
    }

    if (p < King || p > Pawn) { 
      return -5;
    }

    chessboard[x][y] = Square(c, p);
    return 1;
  }

  //Getting attributes of a square
  int get(int x, int y, Color &c, Piece &p) {
    if (x < 0 || x >= 8) { 
      return -1; 
    }

    if (y < 0 || y >= 8) { 
      return -2; 
    }
    
    bool occupied;
    chessboard[x][y].get(occupied, c, p);
    
    if (!occupied) {
      return -3;
    }
    
    return 1;
  }

  //Move a piece from one square to another
  int move(int fromX, int fromY, int toX, int toY) {
    Color fromColor, toColor;
    Piece fromPiece, toPiece;

    //illegal x cords
    if (fromX < 0 || fromX >= 8) return -1;
    if (fromY < 0 || fromY >= 8) return -2;

    //illegal y cords
    if (toX < 0 || toX >= 8) return -3;
    if (toY < 0 || toY >= 8) return -4;
    
    // Check if the origin is occupied
    if (get(fromX, fromY, fromColor, fromPiece) != 1) {
      return -5;
    }

    // Check if destination is occupied by a piece of the same color
    if (get(toX, toY, toColor, toPiece) == 1 && toColor == fromColor) {
      return -6;
    }

    int dx = toX - fromX;
    int dy = toY - fromY;
    
    bool isLegalMove = false;

    // Piece-specific logic
    switch (fromPiece) {
      case Pawn: {
        int direction = (fromColor == White) ? 1 : -1;
        if ((dy == direction && dx == 0 && toColor == UndefinedColor) ||
            (dy == direction && abs(dx) == 1 && toColor != fromColor && toColor != UndefinedColor)) {
          isLegalMove = true;
        }
        break;
      }
      case Rook: {
        if (dx == 0 || dy == 0) {
          isLegalMove = true;
        }
        break;
      }
      case Knight: {
        if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
          isLegalMove = true;
        }
        break;
      }
      case Bishop: {
        if (abs(dx) == abs(dy)) {
          isLegalMove = true;
        }
        break;
      }
      case King: {
        if (abs(dx) <= 1 && abs(dy) <= 1) {
          isLegalMove = true;
        }
        break;
      }
      case Queen: {
        if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) {
          isLegalMove = true;
        }
        break;
      }
      default:
        return -7;
    }

    // If the move is legal, update the board
    if (isLegalMove) {
      // If destination is occupied by an enemy, capture it
      if (toColor != fromColor && toColor != UndefinedColor) {
        cout << "Capturing piece at (" << toX << ", " << toY << ")\n"; // Optionally print a message
      }
      // Move the piece from source to destination
      chessboard[toX][toY] = Square(fromColor, fromPiece);
      chessboard[fromX][fromY] = Square();  // Clear the source square
      return 1;  // Indicate success
    }

    return -7;  // Illegal move
  }

  //Prints out the board (definition in chessboard.h)
  void print();
};


//Class to facilitate iteration over the Chessboard
class ChessboardIterator {
private:
  int position; // a number in [0..63]
  Chessboard &chessboard;

public:
//Constructor
ChessboardIterator(Chessboard &board, int pos)
  : chessboard(board), position(pos) {}

//xy cord conversions
int xy(int &x, int &y) {
    if (position >= 0 && position < 64) {
        x = position % 8;
        y = position / 8;
        return 1;
    }
    return -1;
}

// return the square
Square operator*() {
    int x, y;
    xy(x, y);
    return chessboard.square(x, y);
}

// pre-increment
ChessboardIterator &operator++() {
    ++position;
    return *this;
}

  // needed to support foreach
  bool operator!=(ChessboardIterator &a) {
    return position != a.position;
  }
};
