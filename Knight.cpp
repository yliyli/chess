#include "Knight.h"
#include <cmath>

//Knight travels in an L path - 2*1 formation or 1*2 formation
namespace Chess {

  bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //Column movement variable is set to column_step
    //Row movement variable is set to row_step
    int column_step = abs(start.first - end.first);
    int row_step = abs(start.second - end.second);
    if ((column_step == 1 && row_step == 2) || (column_step == 2 && row_step == 1)) {
      //If the condition is true, the Knight moves in the L-path
      return true;
    }
    return false;
  }
}
