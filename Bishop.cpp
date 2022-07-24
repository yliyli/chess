#include "Bishop.h"
#include <cmath>

//Bishop moves in a diagonal fashion for unlimited tiles


namespace Chess {
  bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //Column movement variable is set to column_step
    //Row movement variable is set to row_step
    int column_step = abs(start.first - end.first);
    int row_step = abs(start.second - end.second);
    //If the row and column movement is the same, the bishop makes a legal move
    //Also check whether it moved from position 0
    if (!(column_step == 0 && row_step == 0) && column_step == row_step) {
      //If the condition is true, the Bishop moves
      return true;
    }
    return false;
  }
}
