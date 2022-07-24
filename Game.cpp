#include <cassert>
#include "Game.h"
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include "Exceptions.h"

using std::cout; using std::endl; using std::map; using std::pair;
using std::make_pair;

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
      board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

    // Add the knights
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

    // Add the bishops
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

    // Add the kings and queens
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
  }

  //copy constructor used during checks
  Game::Game(const Game& game){

    //a nested loop that checks through all pieces on borad then copies
    for (char r = 'A'; r < 'I'; r++) {
      for (char c = '1'; c < '9'; c++) {
	      pair<char,char> location = make_pair(r, c);
	      if (game.board(location)) { //we have a piece here
	        board.add_piece(location, game.board(location)->to_ascii());
	}
      }     
    }
    
    is_white_turn = game.is_white_turn;
  } 

  void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {
    //start by making them all upper case
    start.first = toupper(start.first);
    start.second = toupper(start.second);
    end.first = toupper(end.first);
    end.second = toupper(end.second);

    //first check if positions are valid before anything else,
    if (!board.pos_valid(start)) {
      throw Exception("start position is not on board");
      return;
    }

    if (!board.pos_valid(end)){
      throw Exception("end position is not on board");
      return;
    }
    
    //Then check if the start position does have a piece
    if (!board(start)) {
      throw Exception("no piece at start position");
      return;
    }

    //Then check if the turn is correct
    if (is_white_turn != board(start)->is_white()) {
      throw Exception("piece color and turn do not match");
      return;
    }
    //Then check if the end position does not have a piece or is of different color
    if (board(end) && board(start)->is_white() == board(end)->is_white()) {
      throw Exception("cannot capture own piece");
      return;
    }
    
    //Then check if the path is clear
    if (!board.path_clear(start, end)) {
      throw Exception("path is not clear");
      return;
    }

    //If there is a piece at end position then check capture shape
    if ((board(end)) && !board(start)->legal_capture_shape(start,end)) {
      throw Exception("illegal capture shape");
      return;
    }

    //If there is no piece at end check move shape
    if ((!board(end)) && !board(start)->legal_move_shape(start,end)) {
      throw Exception("illegal move shape");
      return;
    }    
    
    //Then check if this move would cause in_check. 
    //This check is done by making a copy of original board
    Game copy = *this;
    copy.board.make_move(start, end);
    if (copy.in_check(is_white_turn)) {
      throw Exception("move exposes check");
      return;
    }
    
    //Finally we can make move on the actual board
    board.make_move(start, end);
    is_white_turn = !is_white_turn;

    //check promotion for pawn
    char piece = board(end)->to_ascii();
    if ((piece == 'p' || piece == 'P') && board.at_last_row(end)) {
      char queen = 'q';
      if (piece == 'P') queen = 'Q'; //make sure color is correct
      board.remove_piece(end);
      board.add_piece(end, queen);
    }


  }

  bool Game::in_check(bool white) const {
    //first we need the location of the king
    pair<char, char> king;
    for (char r = 'A'; r < 'I'; r++) {
      for (char c = '1'; c < '9'; c++) {
        pair<char,char> location = make_pair(r,c);
        const Piece* npiece = board(location);
        //if there's a piece present
        if(npiece) {
          //if it's a king, we store its position
          if((npiece->to_ascii() == 'K' || npiece->to_ascii() == 'k') && npiece->is_white() == white) {
            king = location;
	    //now we go through and see if any pieces could take the king
            for (char r = 'A'; r < 'I'; r++) {
              for (char c = '1'; c < '9'; c++) {
                pair<char,char> nloc = make_pair(r,c);
                const Piece* capturer = board(nloc);
                //if there's a piece present
                if(capturer) {
                  //check if it's the opposite color
                  if((capturer->is_white() != white)) {
                    //if the piece can legally capture the king and its path is clear
                    //the piece is in check
                    if(capturer->legal_capture_shape(nloc, king) && board.path_clear(nloc, king)){
		      return true;
		    }
                  }
                }
              }
            }
            //if we find the king and there are no pieces to capture it, then we can safely return false
            return false;
          }
        }
      }
    }
    return false;
  }


  bool Game::in_mate(bool white) const {
    //if the player is not in check, they could not be in check mate
    if(!in_check(white)) return false;
    //if there are available moves, this will return false. Otherwise, the player is in
    //check mate (true)
    return !has_available(white);
  }


  bool Game::in_stalemate(bool white) const {
    //if the player's in check, they're not in stalemate
    if(in_check(white)) return false;
    //if there are available moves, this will return false. Otherwise, the player is in
    //stale mate (true)
    return !has_available(white);
  }

  std::istream& operator>> (std::istream& is, Game& game) {
    //trying to read the board in from input stream
    is >> game.board;
    char turn;
    is >> turn;
    if(turn == 'W' || turn == 'w') game.is_white_turn = true;
    else if(turn == 'B' || turn == 'b') game.is_white_turn = false;
    return is;
  }


  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
  }

  bool Game::has_available(bool white) const {
    
    for (char r = 'A'; r < 'I'; r++) {
      for (char c = '1'; c < '9'; c++) {
        //if there's a piece present
        pair<char,char> location = make_pair(r, c);
        const Piece* npiece = board(location);
        if(npiece) {
          //if it's the color we're looking for
          if(npiece->is_white() == white) {
            //we go through every single space on the board and make pairs
            //we then see if it can make a move to every board position
            //if there is at least one possible move, we return true
            for(char i = 'A'; i <= 'H'; i++) {          
              for(char j = '1'; j <= '8'; j++) {
		pair<char,char> position = make_pair(i, j);
                Game copy = *this;
                //we create another copy of the board and plug it into our make_move  
                try{
                  copy.make_move(location, position);
		  //has possible move, return ture
		  return true;
		}//if we don't catch exception, true
                catch(const Chess::Exception &e) {
                  continue;
                }
              }
	    }
	  }
        }
      }
    }
    //if there are no possible moves, we return false
    
    return false;
  }

  
}   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
