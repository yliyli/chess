#include "Pawn.h"
#include <cmath>

//Pawn moves forward by 1
//White Pawns start at Row 2
//Black Pawns start at Row 7
//Pawn cannot move forward to a grid occupied by the opponent's piece
namespace Chess {


  bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //Declaring a boolean that checks if piece is white
    bool white_pawn = this -> is_white();
    
    int column_step = (start.first - end.first);
    int row_step = (end.second - start.second);

    //Check whether pawn does not move down column
    if (column_step != 0) {
      return false;
    }
   
    //Check whether pawn is white and starts at a the beginning position
    //Here the pawn can either move up 1 or 2
    if (start.second == '2' && white_pawn) {
      //Check whether pawn makes a valid movement -- if so, return true
      if (row_step == 1 || row_step == 2) {
	return true;
      }
      return false;
    }
    
    //Check whether pawn is white and does a valid movement off the beginning position
    //Once the pawn leaves its original spot, it can only move up the row by one grid
    if (start.second != '2' && white_pawn) {
      //Check that the pawn only moved up one in the row
      if (row_step == 1) {
	return true;
      }
      return false;
    }


    //Check whether pawn is black and starts at a the beginning position 
    //Again, at the pawn's original position, it can move up 1 or 2 grids
    if (start.second == '7' && !white_pawn) {
      if (row_step == -1 || row_step == -2) {
	return true;
      }
      return false;
    }

    if (start.second != '1' && !white_pawn) {
      if (row_step == -1) {
	return true;
      }
      return false;

    }
    
    return false;
  }


  bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    bool white_pawn = this -> is_white();

    int column_step = (start.first - end.first);
    int row_step = (end.second - start.second);

    if (white_pawn) {
      if (abs(column_step) == 1 && row_step == 1) {
	return true;
      }
      return false;
    }
    else {
      if (abs(column_step) == 1 && row_step == -1) {
	return true;
      }
      return false;
    }
    
  return false;
  }
}
