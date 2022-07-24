#include "Queen.h"
#include <cmath>

//A Queen is able to move an unlimited number of squares in one direction
namespace Chess {

  bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //Column movement variable is set to column_step
    //Row movement variable is set to row_step
    int column_step = abs(start.first - end.first);
    int row_step = abs(start.second - end.second);

    if ((column_step != 0 && row_step == 0) || (column_step == 0 && row_step != 0)) {
      //If Queen moves by row or column, return true
      return true;
    }
    if ((column_step == row_step) && (column_step != 0) && (row_step != 0)) {
      //If Queen moves diagonally, return true
      return true;
    }
    return false;
  
  }
}
