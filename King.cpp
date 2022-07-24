#include "King.h"
#include <cmath>

//King can move anywhere except only one grid
namespace Chess {

  bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //Column movement variable is set to column_step
    //Row movement variable is set to row_step
    int column_step = abs(start.first - end.first);
    int row_step = abs(start.second - end.second);

    //Check if King moves in any direction for one square
    if ((column_step == 0 && row_step == 1) || (column_step == 1 && row_step == 0) || (column_step == 1 && row_step == 1)) {
      return true;
    }
    return false;

  }
}
