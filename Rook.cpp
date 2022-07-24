#include "Rook.h"
#include <cmath>

//Rook can only move vertically or horizontally for an unlimited number of tiles
namespace Chess {

  bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //Column movement variable is set to column_step
    //Row movement variable is set to row_step
    int column_step = abs(start.first - end.first);
    int row_step = abs(start.second - end.second);
    //The Rook can either move by column or row
    if ((column_step != 0 && row_step == 0) || (column_step == 0 && row_step != 0)) {
      return true;
    }
    return false;
  }
}
