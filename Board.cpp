#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "CreatePiece.h"
#include <vector>


using std::vector; using std::endl; using std::cout; using std::map;
using std::pair; using std::make_pair;

namespace Chess
{

  Board::Board(){}

  //destructor 
  Board::~Board() {
    for(map<pair<char, char>,Piece*>::iterator it = occ.begin(); it!= occ.end();
	it++){
      //careful about the piece pointers
      if(it->second != NULL) delete it->second;
    }
    
    occ.clear();
  }

  const Piece* Board::operator()(pair<char, char> position) const {
    //find if this position has a piece
    map<pair<char,char>, Piece*>::const_iterator it = occ.find(position);

    //doesn't exist
    if(it == occ.end()) return NULL;
    //exist
    else return it->second;
  }

  //felt better to make this check into a helper function
  bool Board::pos_valid(std::pair<char, char> position) const {
    char c = toupper(position.first), r = position.second;
    if ((c < 'A' || c > 'H') && (r < '1' || r > '8')) return false;
    return true;
  }
  
  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    // first check if the piece_designator is valid
    //use a switch case to check all posibilities
    switch (piece_designator)
      {
      case 'K':
      case 'k':
      case 'Q':
      case 'q':
      case 'B':
      case 'b':
      case 'N':
      case 'n':
      case 'R':
      case 'r':
      case 'P':
      case 'p': break;
      default: return false; //the piece is invalid if we reach here
      }

    //then check if the position is valid    
    if (!pos_valid(position)) return false;

    //then check if the position is already occupied
    for (map<pair<char, char>, Piece*>::const_iterator it = occ.cbegin(); it != occ.cend();
	it++) {
      if(it->first == position)	return false;
    }

    //finally we can do create piece
    occ[position] = create_piece(piece_designator);
    return true;
  }

  bool Board::has_valid_kings() const {
    //both side should have exactly one king
    int wk = 0, bk = 0;
    
    //iterate through the map to find how many king we have
    for(map<pair<char, char>, Piece*>::const_iterator it = occ.cbegin(); it != occ.cend(); it++) {
      //note that upper-case should match with is_whie
      if(it->second->is_white() && it->second->to_ascii() == 'K') wk++;
      if((!it->second->is_white()) && it->second->to_ascii() == 'k') bk++;     
    }

    //true when both is 1 
    return bk == 1 && wk == 1;
  }


  //Printing the header of the board
  void Board::print_header() const {
    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                                        " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "    ================================    " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "     | | | | BLUE JAY CHESS | | | |     " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "    ================================    " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                                        " << endl;
    Terminal::set_default();
  }

  
  
  //Printing the tiles of the board
  void Board::print_board() const {
    int temp_x = 0;
    for (char row = '8'; row >= '1'; row--) {
      Terminal::color_bg(Terminal::BLUE);
      cout << "        ";
      int temp_y = 0;
      if (temp_x % 2 == 0) {
	temp_y = 1;
      }
      for (char column = 'A'; column <= 'H'; column++) {
	if (temp_y % 2 == 0) {
	  Terminal::color_bg(Terminal::MAGENTA);
	}
	else {
	  Terminal::color_bg(Terminal::GREEN);
	}
	
	const Piece* chess_piece = (*this) (pair<char, char>(column, row));
	if (chess_piece && chess_piece->is_white()) {
	  //Player 1 has white piece colors
	  Terminal::color_fg(true, Terminal::WHITE);
	  cout << " " << chess_piece -> to_ascii() << " ";
	}
	else if(chess_piece && !(chess_piece->is_white())) {
	  //Player 2 has black piece colors
	  Terminal::color_fg(true, Terminal::BLACK);
	  cout << " " << chess_piece -> to_ascii() << " ";
	}
	else {
	  cout << "   ";
	}
	temp_y++;
      }
      Terminal::color_bg(Terminal::BLUE);
      cout << "        " << endl;
      Terminal::set_default();
     
      temp_x++;
      
    }
  
  }

  //Function that outputs the Bird ascii_art
  void Board::ascii_art() const {
    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                                        " << endl;
    Terminal::set_default();
  
    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                  < 0 )                 " << endl;
    Terminal::set_default();


    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                  / ) )                 " << endl;
    Terminal::set_default();


    Terminal::color_all(true, Terminal::BLACK, Terminal::BLUE);
    cout << "                ===#=====               " << endl;
    Terminal::set_default();
  
    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                                        " << endl;
    Terminal::set_default();

  }

  void Board::print_quote() const {
    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "    ================================    " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "      Veritas vos liberabit - 1876      " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "    ================================    " << endl;
    Terminal::set_default();

    Terminal::color_all(true, Terminal::CYAN, Terminal::BLUE);
    cout << "                                        " << endl;
    Terminal::set_default();


  }


  //Displaying the entire board
  //Combining all the previous helper functions in the display
  void Board::display() const {
    
    //Print the header on the board
    print_header();

    //Print the tiles on the board 
    print_board();
    
    //Print the ascii art of the bird on the board
    ascii_art();
 
    //Print the quote on the board
    print_quote();

    
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }

  //remove piece helper function that's used in promotion
  void Board::remove_piece(pair<char, char> pos){
    delete occ[pos];
    //occ[pos] = NULL;
    occ.erase(pos);
  }
  

  //a bunch of helper functions that check if path is clear

  //horizontal check
  bool Board::horizontal(pair<char, char> start, pair<char, char> end) const{
    //for loop is different for left and right
    if((end.first - start.first) > 0){ //this is going right
      for(pair<char,char> i(start.first+1, start.second); i.first != end.first; i.first++){
	if ((*this)(i) != NULL) return false;
      }
    }
    else { //this is going left
      for(pair<char,char> i(start.first-1, start.second); i.first != end.first; i.first--){
	if ((*this)(i) != NULL) return false;
      }
    }
    return true;
  }

  //vertical check
  bool Board::vertical(pair<char, char> start, pair<char, char> end) const{
    //for loop is different for up and down
    if((end.second - start.second) > 0){ //this is going up
      for(pair<char,char> i(start.first, start.second+1); i.second != end.second; i.second++){
	if ((*this)(i) != NULL) return false;
      }
    }
    else { //this is going down
      for(pair<char,char> i(start.first, start.second-1); i.second != end.second; i.second--){
	if ((*this)(i) != NULL) return false;
      }
    }
    return true;
  }

  //diagnal check
  bool Board::diagnal(pair<char, char> start, pair<char, char> end) const{
    //Note that all the for loops below ends by checking only i.first, because that's enough
    //assuming we have complete diagnal movement

    //there are four possible directions
    if((end.first - start.first) > 0 && (end.second - start.second) > 0){
      //this is going up right
      for(pair<char,char> i(start.first+1, start.second+1); i.first != end.first;
	  i.first++, i.second++){
	if ((*this)(i) != NULL) return false;
      }
    } else if((end.first - start.first) < 0 && (end.second - start.second) > 0){
      //this is going up left
      for(pair<char,char> i(start.first-1, start.second+1); i.first != end.first;
	  i.first--, i.second++){
	if ((*this)(i) != NULL) return false;
      }
    } else if((end.first - start.first) > 0 && (end.second - start.second) < 0){
      //this is going down right
      for(pair<char,char> i(start.first+1, start.second-1); i.first != end.first;
	  i.first++, i.second--){
	if ((*this)(i) != NULL) return false;
      }
    }else {//this is going down left
      for(pair<char,char> i(start.first-1, start.second-1); i.first != end.first;
	  i.first--, i.second--){
	if ((*this)(i) != NULL) return false;
      }
    }
    
    return true;
  }

  //complete check that works for all pieces
  //always return true for king and knight
  bool Board::path_clear(pair<char, char> start, pair<char, char> end) const{

    //the && abs(***) > 1 excludes the moves that only move one tile and can't be blocked
    if (start.first - end.first == 0 && abs(start.second - end.second) > 1) {
      //no change in horizontal coordinates, so vertical path
      return vertical(start, end);
    } else if (start.second - end.second == 0 &&  abs(start.first - end.first) > 1) {
      //no change in vertical coordinates, so horizontal path
      return horizontal(start, end);
    } else if (abs(start.first - end.first) == abs(start.second - end.second)) {
      //both coordinates have same changes, so straight diagnal path, excluding "L" shape
      return diagnal(start,end);
    }

    //path that's always clear, ie, king, knight or mystery piece with weird shape
    //or moving just one tile, which should always be clear too
    return true;
  }

  //since Game don't have direct access to board map occ, we need to create helper functions
  //for make_move in board class
  //this returns true if move is valid, false if it is not
  bool Board::make_move(pair<char, char> start, pair<char, char> end){
    //have to check if positions are valid so nothing wrong happens with path clear check
    if(!pos_valid(start) || !pos_valid(end)) return false;
    
    //the destination has no piece and we can just make the move
    if(occ[end] == NULL){
      Piece* n = occ[start];
      occ[end] = n;
      occ.erase(start);
      return true;
    } else {
      //so the destination has a piece and we can only move(capture) if the color is different
      if(occ[start]->is_white() == occ[end]->is_white()) return false; 

      //so the destination now has a piece with different color and we can capture it happily
      delete occ[end];
      Piece* n = occ[start];
      occ[end] = n;
      occ.erase(start);
      return true;      
    }
  }

  //helper function to test if position is last row for promotion
  bool Board::at_last_row(pair<char, char> pos) {
    //have to check if positions are valid so nothing wrong happens
    if(!pos_valid(pos)) return false;

    //last row is different for white and black, so check seperately
    if(occ[pos]->is_white()) { //white piece
      if(pos.second == '8') return true;      
    } else { //black piece
      if(pos.second == '1') return true;
    }   
  
    //the position is not at last row  
    return false;
  }

  
  std::istream& operator>> (std::istream& is, Board& board) {

    board.clear();

    //then we take in every position and make a piece if a piece exists there
    for(char r = '8'; r > '0'; r--){
      for(char c = 'A'; c < 'I'; c++){
        char piece;
        is >> piece;
        char check_piece = toupper(piece);
        if(board.valid_char(check_piece)) {
          pair<char,char> position = make_pair(c,r);
          board.add_piece(position, piece);
        }
      }
    }
    return is;
  }

  //read description in header file
  bool Board::valid_char(char piece) const{
    switch(piece) {
      case 'K':
      case 'Q':
      case 'P':
      case 'B':
      case 'N':
      case 'R':
        return true;
      default:
        return false;
    }
    return false;
  }

  void Board::clear() {
    //clears the board
    for(map<pair<char, char>,Piece*>::iterator it = occ.begin(); it!= occ.end(); it++){
        delete it->second;
    }
    occ.clear();
  }
  
}
