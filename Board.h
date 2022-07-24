#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


namespace Chess
{
  class Board {

    // Throughout, we will be accessing board positions using an std::pair<char, char>.
    // The assumption is that the first value is the column with values in
    // {'A','B','C','D','E','F','G','H'} (all caps)
    // and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

  public:
    // Default constructor
    Board();

    //destructor
    ~Board();

    // Returns a const pointer to the piece at a prescribed location if it exists,
    // or nullptr if there is nothing there.
    const Piece* operator() (std::pair<char, char> position) const;

    // Attempts to add a new piece with the specified designator, at the given location.
    // Returns false if:
    // -- the designator is invalid,
    // -- the specified location is not on the board, or
    // -- if the specified location is occupied
    bool add_piece(std::pair<char, char> position, char piece_designator);
    
    // Displays the board by printing it to stdout
    void display() const;

    // Returns true if the board has the right number of kings on it
    bool has_valid_kings() const;

    //check if the position is valid
    bool pos_valid(std::pair<char, char> position) const;

    //removes a piece from the board at the given location
    void remove_piece(std::pair<char, char> pos);

    //check if the path between start and end is clear
    bool path_clear(std::pair<char, char> start, std::pair<char, char> end) const;

    //helper function for make move in Game
    bool make_move(std::pair<char, char> start, std::pair<char, char> end);

    //checks if the position is at last row
    bool at_last_row(std::pair<char, char> pos);

    //helper function for comparing strings (takes in uppercase)
    bool valid_char(char piece) const;

    // Creates a board state from an input stream
    friend std::istream& operator>> (std::istream& is, Board& board);
    
       
  private:
    // The sparse map storing the pieces, keyed off locations
    std::map<std::pair<char, char>, Piece*> occ;
    
    //three helper functions for path_clear
    bool horizontal(std::pair<char, char> start, std::pair<char, char> end) const;

    bool vertical(std::pair<char, char> start, std::pair<char, char> end) const;

    bool diagnal(std::pair<char, char> start, std::pair<char, char> end) const;

    //Printing the header of the board
    void print_header() const;
    
    //Printing a Board 
    void print_board() const;

    //Printing ascii_art on the board
    void ascii_art() const;

    //Printing Johns Hopkins quote on the board
    void print_quote() const;

    void clear();

  };

  // Write the board state to an output stream
  std::ostream& operator<< (std::ostream& os, const Board& board);

}
#endif // BOARD_H
