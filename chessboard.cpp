/**
 * Author: Tam Le
 * UIN: 674428071
 * File: chessboard.cpp
 * Project: Chessboard Project for CS 341
 * Description:
 * A C++ project that displays an 8x8 chessboard
 * with an iterator over the chessboard. The view
 * of the board is traditional view.
*/

#include "chessboard.h"

/**
 
  Chessboard Iterator

**/

//Function to initialize and return the iterator pointing to the beginning of the chessboard
ChessboardIterator Chessboard::begin() {
  return ChessboardIterator(*this, 0);
}

//Function to initialize and return the iterator pointing to the end of the chessboard
ChessboardIterator Chessboard::end() {
  return ChessboardIterator(*this, 64);
}

//Function to print the chessboard with white at the bottom (traditional view)
void Chessboard::print() {
    // Loop through the board using the iterator
    for (ChessboardIterator theStart = begin(), theEnd = end(); theStart != theEnd; ++theStart) {
        int x, y;
        if (theStart.xy(x, y) == 1) { // Check if the position is valid
            Square currentSquare = *theStart;
            
            //print the details of the currentSquare
            currentSquare.print();
            
            // New line after each row
            if (x == 7) {
                std::cout << std::endl;
            }
        }
    }
}