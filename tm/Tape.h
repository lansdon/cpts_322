//
//  Tape.h
//  tm
//
//	Represents the tape component of the Turing Machine
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__Tape__
#define __tm__Tape__

// STL
#include <iostream>
#include <fstream>
#include <string>

// TM
#include "Direction.h"

using namespace std;

class Tape
{
public:
	Tape();
	
	// method loads the tape from the given definition
	void load(ifstream& definition, bool& valid);
	
	//o	Prints the current tape cells
	void view() const;
	
	//o	Resets the tape with the passed input string
	void initialize(string input_string);
	
	//o	Updates the tape by writing a new character to the current cell and moving the tape head in the specified direction.
	void update(char write_character, Direction move_direction);
	
	/*
	 o	Returns a string representing the cells to the left of the tape head, 
	 truncated to the max number of cells argument. 
	 Truncated strings will have a < inserted at the 
	 beginning to indicate it was truncated.
	 */
	string left(unsigned long maximum_number_of_cells) const;
	
	/*
	 Returns the current cell and the cells to the right of the current cell, 
	 truncated according to the max number of cells argument. Truncated 
	 strings will have a > appended to the end to indicate it was truncated.
	*/
	string right(unsigned long maximum_number_of_cells) const;
	
	//o	Returns the character at the current cell
	char current_character() const { return cells[current_cell]; };
	
	// Return blank char
	char blank_character() const { return blank; };
	
	// Returns if head is on first cell
	bool is_first_cell() const { return (current_cell == 0); };	
	
private:
	// This is the list of characters as they appear on the tape, starting at cell 0.
	string cells;
	//o	the cell where the tape head is located
	int current_cell;
	// The blank character specified by the TM Definition.
	char blank;
};


#endif /* defined(__tm__Tape__) */
